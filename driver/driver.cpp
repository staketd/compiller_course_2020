#include <driver.h>
#include "parser.hh"
#include <Frame.h>
#include <BuildSymbolLayerTree.h>
#include <TypeChecker.h>
#include <FunctionCallVisitor.h>
#include <IRTreeBuildVisitor.h>
#include <IRPrintVisitor.h>
#include <EliminateDoubleCalls.h>
#include <EliminateEseq.h>
#include <LinearizeIRTree.h>
#include <Block.h>
#include <Print.h>
#include <AsmGenerator.h>
#include <algorithm>
#include <ElementSet.h>
#include <Instructions.h>

Driver::Driver()
    : trace_parsing(false),
      trace_scanning(false),
      scanner(*this),
      parser(scanner, *this),
      global_scope_(new ScopeLayer()) {
  for (size_t i = 0; i < colors_ + 2; ++i) {
    reg_map_[x86_regs_[i]] = static_cast<RegType>(i);
  }
}

int Driver::Parse(const std::string& f) {
  file = f;
  location.initialize(&file);
  InitiateScan();
  parser.set_debug_level(trace_parsing);
  int res = parser();
  std::cout << "parser result: " << res << "\n";
  FinishScan();
  return res;
}

void Driver::InitiateScan() {
  scanner.set_debug(trace_scanning);
  if (file.empty() || file == "-") {
    return;
  }
  stream_.open(file);
  std::cout << file << std::endl;
  scanner.yyrestart(&stream_);
}

void Driver::FinishScan() {
  stream_.close();
}

void Driver::Evaluate() {
  BuildSymbolTree();
  CheckTypes();

  Frame main_frame;

  FunctionCallVisitor visitor(
      std::move(main_frame), func_map_, global_scope_,
      global_scope_.Get(Symbol(program->main_->name_ + "::main")), nullptr,
      class_map_);
  visitor.ExecuteCode(func_map_.Get(Symbol(program->main_->name_ + "::main")));
}

void Driver::Print(const std::string& suffix) {
  if (divided_into_traces_) {
    PrintByTraces(suffix);
    return;
  }
  if (linear_) {
    PrintByStatements(suffix);
    return;
  }
  for (auto method : methods_) {
    std::ofstream stream(method.first.GetName() + suffix + ".txt");
    ir_tree::IRPrintVisitor printer(stream);
    ir_tree::IRStatement* stmt = method.second->ToStatement();
    stmt->AcceptVisitor(&printer);
  }
}

void Driver::BuildSymbolTree() {
  BuildSymbolLayerTree build(global_scope_, func_map_, class_map_);
  build.BuildTree(program);
}

void Driver::CheckTypes() {
  TypeChecker checker(global_scope_.GetRoot(), func_map_, global_scope_);
  checker.CheckType(program);
}

void Driver::Compile() {
  IRTreeBuildVisitor builder(class_map_);
  builder.Build(program);
  methods_ = builder.GetMethods();
  Print("");

  for (auto& method : methods_) {
    ir_tree::EliminateDoubleCalls eliminate_double_calls;
    method.second->ToStatement()->AcceptVisitor(&eliminate_double_calls);
    method.second = eliminate_double_calls.GetTree();
  }
  Print("DCalls");
  for (auto& method : methods_) {
    ir_tree::EliminateEseq eliminate_eseqs;

    method.second->ToStatement()->AcceptVisitor(&eliminate_eseqs);
    method.second = new ir_tree::StatementWrapper(eliminate_eseqs.GetTree());
  }
  Print("NoEseqs");
  for (auto& method : methods_) {
    ir_tree::LinearizeIRTree linearize;

    method.second->ToStatement()->AcceptVisitor(&linearize);
    method.second = new ir_tree::StatementWrapper(linearize.GetTree());

    method_stmts_[method.first] = linearize.GetStatementList();
  }
  linear_ = true;
  Print("Linear");

  DivideIntoBlocks();

  divided_into_traces_ = true;

  Print("Traces");

  BuildAsm();
}

void Driver::PrintByStatements(const std::string& suffix) const {
  for (auto method : method_stmts_) {
    std::ofstream stream(method.first.GetName() + "_" + suffix + ".txt");
    ir_tree::IRPrintVisitor printer(stream);
    for (auto stmt : method.second) {
      stmt->AcceptVisitor(&printer);
    }
  }
}

void Driver::DivideIntoBlocks() {
  for (auto& method : method_stmts_) {
    auto blocks = DivideMethod(method.second);
    blocks.back().SetJump(new ir_tree::JumpStatement(
        ir_tree::Label(method.first.GetName() + "_done")));
    blocks.back().last_block_ = true;

    method_traces_[method.first] = ReorderBlocks(blocks);
  }
}

std::vector<ir_tree::Block> Driver::DivideMethod(
    std::vector<ir_tree::IRStatement*>& statements) {
  std::vector<ir_tree::Block> blocks;
  blocks.emplace_back();
  for (auto stmt : statements) {
    auto& block = blocks.back();
    switch (stmt->GetType()) {
      case ir_tree::IRNodeType::Label: {
        auto label = dynamic_cast<ir_tree::LabelStatement*>(stmt);
        if (block.GetLabel() == nullptr) {
          block.SetLabel(label);
        } else {
          if (block.GetJump() == nullptr) {
            block.SetJump(new ir_tree::JumpStatement(label->label_));
          }
          blocks.emplace_back();
          blocks.back().SetLabel(label);
        }
        break;
      }
      case ir_tree::IRNodeType::Jump: {
        auto jump = dynamic_cast<ir_tree::JumpStatement*>(stmt);
        block.SetJump(jump);
        break;
      }
      case ir_tree::IRNodeType::CJump: {
        auto cjump = dynamic_cast<ir_tree::JumpConditionalStatement*>(stmt);
        block.SetJump(cjump);
        break;
      }
      default:
        block.AddStatement(stmt);
    }
  }
  return blocks;
}

std::vector<ir_tree::Trace> Driver::ReorderBlocks(
    std::vector<ir_tree::Block>& blocks) {
  std::vector<ir_tree::Trace> result;
  std::unordered_map<std::string, ir_tree::Block*> block_by_label;
  std::unordered_map<std::string, bool> used;
  for (auto& block : blocks) {
    block_by_label[block.GetLabel()->label_.ToString()] = &block;
  }

  for (size_t i = 0; i < blocks.size(); ++i) {
    auto& block = blocks[i];
    if (used[block.GetLabel()->label_.ToString()]) {
      continue;
    }
    result.emplace_back();
    ir_tree::Block* now_block = &block;
    while (now_block != nullptr &&
           !used[now_block->GetLabel()->label_.ToString()]) {
      used[now_block->GetLabel()->label_.ToString()] = true;
      result.back().AddBlock(*now_block);
      if (now_block->GetJump()->GetType() == ir_tree::IRNodeType::CJump) {
        auto jump = dynamic_cast<ir_tree::JumpConditionalStatement*>(
            now_block->GetJump());
        now_block = block_by_label[jump->label_false_.ToString()];
      } else {
        auto jump = dynamic_cast<ir_tree::JumpStatement*>(now_block->GetJump());
        now_block = block_by_label[jump->label_.ToString()];
      }
    }
  }

  return result;
}

void Driver::PrintByTraces(const std::string& suffix) {
  size_t trace_ind = 0;
  for (auto& method : method_traces_) {
    std::ofstream out(method.first.GetName() + "_" + suffix + ".txt");
    ir_tree::IRPrintVisitor printer(out);
    for (ir_tree::Trace& trace : method.second) {
      MyPrint(out, "Trace №", trace_ind, "###################\n");
      size_t block_ind = 0;
      for (auto& block : trace.GetBlocks()) {
        MyPrint(out, "Block №", block_ind, "-------------------\n");
        block.GetLabel()->AcceptVisitor(&printer);
        for (auto& stmt : block.GetStatements()) {
          stmt->AcceptVisitor(&printer);
        }
        block.GetJump()->AcceptVisitor(&printer);
        block_ind++;
      }
      trace_ind++;
    }
  }
}

void Driver::PrintAsm(std::ostream& stream) {
  generator_->PrintAll(stream);
}

void Driver::BuildAsm() {
  ir_tree::AsmGenerator generator(program->main_->name_ + "__main");
  generator_ = &generator;
  for (auto& method : method_traces_) {
    bool printed_prologue = false;
    std::string label_name;
    for (auto& trace : method.second) {
      for (auto& block : trace.GetBlocks()) {
        block.GetLabel()->AcceptVisitor(&generator);
        if (!printed_prologue) {
          generator.AddPrologue();
          printed_prologue = true;
          label_name = block.GetLabel()->label_.ToString();
        }
        for (auto& stmt : block.GetStatements()) {
          stmt->AcceptVisitor(&generator);
        }
        block.GetJump()->AcceptVisitor(&generator);
      }
    }
    (new ir_tree::LabelStatement(ir_tree::Label(label_name + "_done")))
        ->AcceptVisitor(&generator);
    generator.AddEpilogue();
  }
  std::ofstream not_painted("Asm_not_painted.s");
  std::ofstream painted("Asm.s");
  generator.PrintAll(not_painted);
  not_painted.flush();
  BuildInOut();
  BuildRegGraph();
  PaintRegs();
  generator_->PrintAll(painted);
}

void Driver::TopSort(size_t v, InstGraph& graph, std::vector<bool>& used,
                     std::vector<size_t>& ans) {
  used[v] = true;
  for (auto to : graph[v]) {
    if (!used[to]) {
      TopSort(to, graph, used, ans);
    }
  }
  ans.push_back(v);
}

void Driver::BuildInOut() {
  auto& instructions = generator_->GetInstructions();
  for (auto x : generator_->GetInstructions()) {
    for (auto reg : x->GetDef()) {
      reg_list_.push_back(reg);
    }
    for (auto reg : x->GetUse()) {
      reg_list_.push_back(reg);
    }
  }
  std::sort(reg_list_.begin(), reg_list_.end());
  reg_list_.erase(std::unique(reg_list_.begin(), reg_list_.end()),
                  reg_list_.end());
  inst_graph_ = BuildInstGraph();
  support_ = new ElementSetk(reg_list_);
  size_t n = inst_graph_.size();

  InstGraph rev_inst_graph(n);
  for (size_t i = 0; i < n; ++i) {
    for (auto y : inst_graph_[i]) {
      rev_inst_graph[y].push_back(i);
    }
  }
  std::vector<size_t> top_sort;
  std::vector<bool> used(n, false);
  in_.resize(n);
  out_.resize(n);
  for (size_t i = 0; i < n; ++i) {
    if (!used[i]) {
      TopSort(i, rev_inst_graph, used, top_sort);
    }
  }
  bool changed = true;
  while (changed) {
    changed = false;
    for (auto i : top_sort) {
      Set in_old = in_[i];
      Set out_old = out_[i];
      Set use = support_->GetSet(instructions[i]->GetUse());
      Set def = support_->GetSet(instructions[i]->GetDef());
      in_[i] = use.Union(out_[i].Complement(def));
      for (auto to : inst_graph_[i]) {
        out_[i].SelfUnion(in_[to]);
      }
      if (!changed) {
        changed = in_old.IsDifferFrom(in_[i]) || out_old.IsDifferFrom(out_[i]);
      }
    }
  }
}

Driver::InstGraph Driver::BuildInstGraph() {
  size_t n = generator_->GetInstructions().size();
  auto& instructions = generator_->GetInstructions();
  std::unordered_map<std::string, int> labels;
  size_t ind = 0;
  for (auto inst : instructions) {
    if (inst->Type() == AsmType::Label) {
      auto label = dynamic_cast<LabelInstruction*>(inst);
      labels[label->label_] = ind;
    }
    ind++;
  }
  ind = 0;
  std::vector<std::vector<size_t>> graph(n);
  for (auto inst : instructions) {
    if (ind + 1 < n) {
      graph[ind].push_back(ind + 1);
    }

    if (inst->Type() == AsmType::Jump) {
      auto jump = dynamic_cast<JumpInstruction*>(inst);
      graph[ind].push_back(labels[jump->label_]);
    }
    ind++;
  }
  return graph;
}

Driver::RegGraph Driver::BuildRegGraph() {
  size_t n = reg_list_.size();
  adj_regs_.resize(n);
  reg_graph_.resize(n);
  for (size_t from = 0; from < inst_graph_.size(); ++from) {
    for (auto to : inst_graph_[from]) {
      auto set = support_->GetIndexes(out_[from].Intersect(in_[to]));
      for (size_t i = 0; i < set.size(); ++i) {
        for (size_t j = i + 1; j < set.size(); ++j) {
          reg_graph_[set[i]].push_back({set[j], false});
          reg_graph_[set[j]].push_back({set[i], false});
        }
      }
    }
  }
  for (size_t i = 0; i < generator_->GetInstructions().size(); ++i) {
    auto inst = generator_->GetInstructions()[i];
    if (inst->Type() == AsmType::Mov) {
      auto mov = dynamic_cast<MovInstruction*>(inst);
      if (CheckConst(mov->source_)) {
        continue;
      }
      auto a = support_->GetIndexes(mov->GetDef())[0];
      auto b = support_->GetIndexes(mov->GetUse())[0];
      reg_graph_[a].push_back({b, true});
      reg_graph_[b].push_back({a, true});
    }
  }
  for (size_t i = 0; i < n; ++i) {
    auto& x = reg_graph_[i];
    x.erase(std::unique(x.begin(), x.end()), x.end());
    adj_regs_[i] = x.size();
  }
  return reg_graph_;
}

void Driver::PaintRegs() {
  size_t n = reg_list_.size();
  std::vector<size_t> regs_stack;
  reg_color_.resize(n);
  std::vector<bool> has_color(n, false);
  for (size_t i = 0; i < n; ++i) {
    if (reg_map_.find(reg_list_[i]) != reg_map_.end()) {
      reg_color_[i] = reg_map_[reg_list_[i]];
      has_color[i] = true;
    }
  }
  std::vector<bool> used(n, false);
  while (regs_stack.size() < n) {
    for (size_t i = 0; i < n; ++i) {
      if (!used[i]) {
        TrySimplify(i, used, regs_stack);
      }
    }
    for (size_t i = 0; i < n; ++i) {
      if (!used[i]) {
        regs_stack.push_back(i);
        for (auto [to, type] : reg_graph_[i]) {
          if (!used[to]) {
            adj_regs_[to]--;
          }
        }
        break;
      }
    }
  }
  size_t need_to_store = 0;
  std::vector<bool> stack_stored(n, false);
  std::vector<size_t> offset(n, 0);
  while (!regs_stack.empty()) {
    auto top = regs_stack.back();
    regs_stack.pop_back();
    if (has_color[top]) {
      continue;
    }
    std::vector<bool> used_color(colors_ + 2, false);
    for (auto [to, type] : reg_graph_[top]) {
      if (has_color[to]) {
        used_color[static_cast<size_t>(reg_color_[to])] = true;
      }
    }
    bool painted = false;
    for (size_t i = 0; i < colors_; ++i) {
      if (!used_color[i]) {
        painted = true;
        has_color[top] = true;
        reg_color_[top] = static_cast<RegType>(i);
        break;
      }
    }
    if (!painted) {
      offset[top] = need_to_store * 8;
      stack_stored[top] = true;
      ++need_to_store;
    }
  }
  change_reg_to_ = reg_list_;
  for (size_t i = 0; i < n; ++i) {
    if (!stack_stored[i]) {
      change_reg_to_[i] = x86_regs_[static_cast<size_t>(reg_color_[i])];
    } else {
      change_reg_to_[i] = "[rbp-" + std::to_string(offset[i]) + "]";
    }
  }
  for (size_t i = 0; i < generator_->GetInstructions().size(); ++i) {
    generator_->GetInstructions()[i]->ChangeNames(support_, change_reg_to_);
  }
}

void Driver::TrySimplify(size_t v, std::vector<bool>& used,
                         std::vector<size_t>& stack) {
  if (adj_regs_[v] > colors_) {
    return;
  }
  used[v] = true;
  stack.push_back(v);
  for (auto [to, type] : reg_graph_[v]) {
    if (!used[to]) {
      adj_regs_[to]--;
    }
  }
  for (auto [to, type] : reg_graph_[v]) {
    if (!used[to]) {
      TrySimplify(to, used, stack);
    }
  }
}

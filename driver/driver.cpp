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

Driver::Driver()
    : trace_parsing(false),
      trace_scanning(false),
      scanner(*this),
      parser(scanner, *this),
      global_scope_(new ScopeLayer()) {
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

void Driver::BuildIrTree() {
  IRTreeBuildVisitor builder;
  builder.Build(program);
  methods_ = builder.GetMethods();

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

  PrintAsm("");
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

void Driver::PrintAsm(const std::string& suffix) {
  auto file_name = "asm" + suffix + ".S";
  ir_tree::AsmGenerator generator(file_name, program->main_->name_ + "__main");
  for (auto& method : method_traces_) {
    bool printed_prologue = false;
    std::string label_name;
    for (auto& trace : method.second) {
      for (auto& block : trace.GetBlocks()) {
        block.GetLabel()->AcceptVisitor(&generator);
        if (!printed_prologue) {
          generator.PrintPrologue();
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
    generator.PrintEpilogue();
  }
  generator.PrintAll();
}

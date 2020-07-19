#include <driver.h>
#include "parser.hh"
#include <Frame.h>
#include <BuildSymbolLayerTree.h>
#include <TypeChecker.h>
#include <ClassMethod.h>
#include <FunctionCallVisitor.h>
#include <IRTreeBuildVisitor.h>
#include <IRPrintVisitor.h>
#include <EliminateDoubleCalls.h>
#include <EliminateEseq.h>
#include <LinearizeIRTree.h>

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

void Driver::Print(const std::string& suffix) const {
  if (linear_) {
    PrintByStatements(suffix);
    return;
  }
  for (auto method : methods_) {
    ir_tree::IRPrintVisitor printer(method.first.GetName() + suffix + ".txt");
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
}

void Driver::PrintByStatements(const std::string& suffix) const {
  for (auto method : method_stmts_) {
    ir_tree::IRPrintVisitor printer(method.first.GetName() + "_" + suffix +
                                    ".txt");
    for (auto stmt : method.second) {
      stmt->AcceptVisitor(&printer);
    }
  }
}

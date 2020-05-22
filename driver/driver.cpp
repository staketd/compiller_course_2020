#include <driver.h>
#include "parser.hh"
#include <Frame.h>
#include <BuildSymbolLayerTree.h>
#include <TypeChecker.h>
#include <ClassMethod.h>
#include <FunctionCallVisitor.h>

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

void Driver::Print() const {
}

void Driver::BuildSymbolTree() {
  BuildSymbolLayerTree build(global_scope_, func_map_, class_map_);
  build.BuildTree(program);
}

void Driver::CheckTypes() {
  TypeChecker checker(global_scope_.GetRoot(), func_map_, global_scope_);
  checker.CheckType(program);
}

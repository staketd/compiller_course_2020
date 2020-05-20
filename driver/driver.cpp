#include <driver.h>
#include "parser.hh"
#include <Frame.h>
#include <BuildSymbolLayerTree.h>
#include <TypeChecker.h>
#include <Function.h>
#include <FunctionCallVisitor.h>

Driver::Driver()
    : trace_parsing(false),
      trace_scanning(false),
      scanner(*this),
      parser(scanner, *this),
      global_scope_(new ScopeLayer()) {
  variables["one"] = 1;
  variables["two"] = 2;
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

  FunctionCallVisitor visitor(std::move(main_frame), map_, global_scope_,
                              global_scope_.Get(Symbol("main")));
  visitor.ExecuteCode(map_.Get(Symbol("main")));
}

void Driver::Print() const {
}

void Driver::BuildSymbolTree() {
  BuildSymbolLayerTree build(global_scope_, map_);
  build.BuildTree(program);
}

void Driver::CheckTypes() {
  TypeChecker checker(global_scope_.GetRoot(), map_);
  checker.CheckType(program);
}

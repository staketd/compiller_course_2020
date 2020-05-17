#include <driver.h>
#include "parser.hh"

#include <Interprenter.h>
#include <PrintTreeVisitor.h>
#include <BuildSymbolLayerTree.h>

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
  stream.open(file);
  std::cout << file << std::endl;
  scanner.yyrestart(&stream);
}

void Driver::FinishScan() {
  stream.close();
}

void Driver::Evaluate() const {
  Interprenter interprenter(global_scope_.GetRoot());
  interprenter.ExecuteCode(program);
}

void Driver::Print() const {
}

void Driver::BuildSymbolTree() {
  BuildSymbolLayerTree build(global_scope_.GetRoot());
  build.BuildTree(program);
}

#pragma once

#include <map>
#include <string>
#include <fstream>
#include <scanner.h>
#include <parser.hh>
#include <grammar/Program.h>
#include <ScopeLayerTree.h>
#include <FunctionMap.h>
#include <ClassMap.h>

class Driver {
 public:
  Driver();
  int result;
  std::string file;
  bool trace_parsing;
  bool trace_scanning;
  Scanner scanner;
  yy::location location;
  yy::parser parser;
  Program* program;
  FunctionMap func_map_;
  ClassMap class_map_;

  void InitiateScan();
  void FinishScan();
  void Evaluate();
  void BuildSymbolTree();
  void BuildIrTree();
  void CheckTypes();
  void Print(const std::string&) const;
  void PrintByStatements(const std::string&) const;

  int Parse(const std::string& f);
  friend class Scanner;

 private:
  std::unordered_map<Symbol, ir_tree::SubtreeWrapper*> methods_;
  std::unordered_map<Symbol, std::vector<ir_tree::IRStatement*>> method_stmts_;

  bool linear_ = false;

  std::ifstream stream_;
  ScopeLayerTree global_scope_;
};

#include "parser.hh"

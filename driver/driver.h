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
#include <Block.h>
#include <Trace.h>
#include <AsmGenerator.h>
#include <ElementSet.h>

class Driver {
 public:
  Driver();
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
  void Compile();
  void CheckTypes();
  void Print(const std::string&);
  void PrintByStatements(const std::string&) const;
  void PrintByTraces(const std::string&);
  void PrintAsm(std::ostream&);

  int Parse(const std::string& f);
  friend class Scanner;

 private:
  using InstGraph = std::vector<std::vector<size_t>>;
  using RegGraph = std::vector<std::vector<std::pair<size_t, bool>>>;
  void DivideIntoBlocks();
  void BuildAsm();
  void BuildInOut();
  void PaintRegs();
  void TopSort(size_t, InstGraph&, std::vector<bool>&, std::vector<size_t>&);

  void TrySimplify(size_t, std::vector<bool>& used, std::vector<size_t>& stack);

  RegGraph BuildRegGraph();
  InstGraph BuildInstGraph();
  std::vector<ir_tree::Block> DivideMethod(std::vector<ir_tree::IRStatement*>&);
  std::vector<ir_tree::Trace> ReorderBlocks(std::vector<ir_tree::Block>&);
  std::vector<size_t> adj_regs_;

  std::unordered_map<Symbol, ir_tree::SubtreeWrapper*> methods_;
  std::unordered_map<Symbol, std::vector<ir_tree::IRStatement*>> method_stmts_;
  std::unordered_map<Symbol, std::vector<ir_tree::Trace>> method_traces_;
  std::unordered_map<Symbol, size_t> decl_count_;

  ir_tree::AsmGenerator* generator_;

  ElementSetk* support_;

  enum class RegType {
    rax,
    rdx,
    rsi,
    rdi,
    rbx,
    r8,
    r9,
    r10,
    r11,
    r12,
    r13,
    r14,
    r15,
    rbp,
    rsp
  };

  std::unordered_map<std::string, RegType> reg_map_;

  const size_t colors_ = x86_regs.size() - 2;
  std::vector<RegType> reg_color_;
  std::vector<std::string> change_reg_to_;
  std::vector<Set> in_;
  std::vector<Set> out_;
  std::vector<std::string> reg_list_;

  InstGraph inst_graph_;
  RegGraph reg_graph_;

  bool linear_ = false;
  bool divided_into_traces_ = false;

  std::ifstream stream_;
  ScopeLayerTree global_scope_;
};

#include "parser.hh"

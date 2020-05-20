
#include "FunctionTable.h"

void FunctionTable::SetIndex(const Symbol& variable, int index) {
  CheckDeclaration(variable);
  table_[variable].back() = index;
}

void FunctionTable::DeclareVariable(const Symbol& variable, int index) {
  if (table_.find(variable) == table_.end()) {
    table_[variable] = std::vector<int>();
  }
  table_[variable].push_back(index);
}

int FunctionTable::GetIndex(const Symbol& variable) {
  CheckDeclaration(variable);
  return table_[variable].back();
}

void FunctionTable::CheckDeclaration(const Symbol& variable) {
  if (table_.find(variable) == table_.end()) {
    throw std::runtime_error("Variable \"" + variable.GetName() +
                             "\" is not declared");
  }
}

void FunctionTable::BeginScope() {
  scopes_symbol_stack_.push_back(Symbol("{"));
}

void FunctionTable::EndScope() {
  while (scopes_symbol_stack_.back() != Symbol("{")) {
    Symbol top_symb = scopes_symbol_stack_.back();
    table_[top_symb].pop_back();

    if (table_[top_symb].empty()) {
      table_.erase(top_symb);
    }
    scopes_symbol_stack_.pop_back();
  }
  scopes_symbol_stack_.pop_back();
}

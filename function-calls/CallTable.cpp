
#include "CallTable.h"

void CallTable::SetIndex(const Symbol& variable, int index) {
  CheckDeclaration(variable);
  table_[variable].back() = index;
}

void CallTable::DeclareVariable(const Symbol& variable, int index) {
  if (table_.find(variable) == table_.end()) {
    table_[variable] = std::vector<int>();
  }
  table_[variable].push_back(index);
  scopes_symbol_stack_.push_back(variable);
}

int CallTable::GetIndex(const Symbol& variable) {
  CheckDeclaration(variable);
  return table_[variable].back();
}

void CallTable::CheckDeclaration(const Symbol& variable) {
  if (table_.find(variable) == table_.end()) {
    throw std::runtime_error("Variable \"" + variable.GetName() +
                             "\" is not declared");
  }
}


void CallTable::BeginScope() {
  scopes_symbol_stack_.push_back(Symbol("{"));
}

void CallTable::EndScope() {
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

bool CallTable::HasVariable(const Symbol& variable) {
  return table_.find(variable) != table_.end();
}

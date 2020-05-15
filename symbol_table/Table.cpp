
#include "Table.h"
#include <UninitObject.h>

void Table::BeginScope() {
    scopes_symbol_stack_.emplace_back("{");
}

void Table::EndScope() {
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

void Table::SetValue(const Symbol& variable, const std::shared_ptr<BaseObject>& obj) {
    if (table_.find(variable) == table_.end()) {
        throw std::runtime_error("Variable is not declared");
    }
    table_[variable].pop_back();
    table_[variable].push_back(obj);
}

void Table::DeclareVariable(const Symbol& variable) {
    table_[variable].push_back(std::shared_ptr<UninitObject>());
    scopes_symbol_stack_.push_back(variable);
}

std::shared_ptr<BaseObject> Table::GetValue(const Symbol& variable) {
    if (table_.find(variable) == table_.end()) {
        throw std::runtime_error("Variable is not declared");
    }
    return table_[variable].back();
}



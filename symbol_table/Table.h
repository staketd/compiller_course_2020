
#ifndef MYCOMPILLER_TABLE_H
#define MYCOMPILLER_TABLE_H

#include <unordered_map>
#include <Symbol.h>
#include <vector>
#include <BaseObject.h>

class Table {
public:
    Table();

private:
    std::unordered_map<Symbol, std::vector<BaseObject>> table_;
    std::unordered_map<std::string, Symbol> name_to_symbol_;
    std::vector<Symbol> scopes_symbol_stack_;
};


#endif //MYCOMPILLER_TABLE_H

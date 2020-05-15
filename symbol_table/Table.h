
#ifndef MYCOMPILLER_TABLE_H
#define MYCOMPILLER_TABLE_H

#include <unordered_map>
#include <Symbol.h>
#include <vector>
#include <BaseObject.h>
#include <memory>

class Table {
public:
    Table() = default;

    void SetValue(const Symbol& variable, const std::shared_ptr<BaseObject>& obj);
    void DeclareVariable(const Symbol&);

    std::shared_ptr<BaseObject> GetValue(const Symbol& variable);

    void BeginScope();
    void EndScope();
private:
    std::unordered_map<Symbol, std::vector<std::shared_ptr<BaseObject>>> table_;
    std::unordered_map<std::string, Symbol> name_to_symbol_;
    std::vector<Symbol> scopes_symbol_stack_;
};


#endif //MYCOMPILLER_TABLE_H

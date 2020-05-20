
#ifndef MYCOMPILLER_FUNCTIONTABLE_H
#define MYCOMPILLER_FUNCTIONTABLE_H
#include <vector>
#include <unordered_map>
#include <Symbol.h>

class FunctionTable {
 public:
  FunctionTable() = default;

  void SetIndex(const Symbol&, int);
  void DeclareVariable(const Symbol&, int index);

  int GetIndex(const Symbol& variable);

  void BeginScope();
  void EndScope();

 private:
  void CheckDeclaration(const Symbol& variable);

 private:
  std::unordered_map<Symbol, std::vector<int>> table_;
  std::vector<Symbol> scopes_symbol_stack_;
};

#endif  // MYCOMPILLER_FUNCTIONTABLE_H


#ifndef MYCOMPILLER_FUNCTIONMAP_H
#define MYCOMPILLER_FUNCTIONMAP_H
#include <Symbol.h>
#include <unordered_map>
#include <Function.h>

class FunctionMap {
 public:
  FunctionMap() = default;
  void Set(const Symbol&, Function*);
  Function* Get(const Symbol&);

 private:
  std::unordered_map<Symbol, Function*> functions_;
};

#endif  // MYCOMPILLER_FUNCTIONMAP_H

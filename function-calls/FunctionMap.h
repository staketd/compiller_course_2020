
#ifndef MYCOMPILLER_FUNCTIONMAP_H
#define MYCOMPILLER_FUNCTIONMAP_H
#include <Symbol.h>
#include <unordered_map>
#include <ClassMethod.h>

class FunctionMap {
 public:
  FunctionMap() = default;
  void Set(const Symbol&, ClassMethod*);
  ClassMethod* Get(const Symbol&);

 private:
  std::unordered_map<Symbol, ClassMethod*> functions_;
};

#endif  // MYCOMPILLER_FUNCTIONMAP_H

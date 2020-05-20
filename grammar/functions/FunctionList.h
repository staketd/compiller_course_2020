
#ifndef MYCOMPILLER_FUNCTIONLIST_H
#define MYCOMPILLER_FUNCTIONLIST_H
#include <BaseASTClass.h>
#include <vector>
#include <Function.h>


class FunctionList : public BaseASTClass {
 public:
  FunctionList() = default;
  void AddFunction(Function*);
  void AcceptVisitor(BaseVisitor*) override;

 public:
  std::vector<Function*> functions_;
};

#endif  // MYCOMPILLER_FUNCTIONLIST_H

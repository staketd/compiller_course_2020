
#ifndef MYCOMPILLER_CALLARGUMENTLIST_H
#define MYCOMPILLER_CALLARGUMENTLIST_H

#include <BaseASTClass.h>
#include <vector>

class CallArgumentList : public BaseASTClass {
 public:
  CallArgumentList() = default;
  void AcceptVisitor(BaseASTVisitor*) override;
  void AddArgument(Expression*);

 public:
  std::vector<Expression*> arguments_;
};

#endif  // MYCOMPILLER_CALLARGUMENTLIST_H

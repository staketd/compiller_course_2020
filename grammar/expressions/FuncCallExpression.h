
#ifndef MYCOMPILLER_FUNCCALLEXPRESSION_H
#define MYCOMPILLER_FUNCCALLEXPRESSION_H
#include <Expression.h>
#include <CallArgumentList.h>
#include <string>

class FuncCallExpression : public Expression {
 public:
  FuncCallExpression(const std::string&, CallArgumentList*);
  void AcceptVisitor(BaseVisitor*);

 public:
  CallArgumentList* arguments_;
  std::string name_;
};

#endif  // MYCOMPILLER_FUNCCALLEXPRESSION_H

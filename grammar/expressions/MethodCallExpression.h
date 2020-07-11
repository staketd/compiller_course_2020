
#ifndef MYCOMPILLER_METHODCALLEXPRESSION_H
#define MYCOMPILLER_METHODCALLEXPRESSION_H
#include <Expression.h>
#include <CallArgumentList.h>
#include <string>

class MethodCallExpression : public Expression {
 public:
  MethodCallExpression(Expression*, const std::string&, CallArgumentList*);
  void AcceptVisitor(BaseASTVisitor*);

 public:
  Expression* expression_;
  CallArgumentList* arguments_;
  std::string name_;
  std::string class_type_name_;
};

#endif  // MYCOMPILLER_METHODCALLEXPRESSION_H


#ifndef MYCOMPILLER_ARRAYEXPRESSION_H
#define MYCOMPILLER_ARRAYEXPRESSION_H
#include <Expression.h>
class ArrayExpression : public Expression {
 public:
  ArrayExpression(const std::string&, Expression*);
  void AcceptVisitor(BaseASTVisitor*) override;

 public:
  std::string name_;
  Expression* expression_;
};

#endif  // MYCOMPILLER_ARRAYEXPRESSION_H

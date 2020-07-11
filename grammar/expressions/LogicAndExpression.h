
#ifndef MYCOMPILLER_LOGICANDEXPRESSION_H
#define MYCOMPILLER_LOGICANDEXPRESSION_H
#include <BinaryExpression.h>

class LogicAndExpression : public BinaryExpression {
 public:
  using BinaryExpression::BinaryExpression;
  void AcceptVisitor(BaseASTVisitor*) override;
};

#endif  // MYCOMPILLER_LOGICANDEXPRESSION_H

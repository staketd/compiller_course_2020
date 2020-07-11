
#ifndef MYCOMPILLER_LOGICOREXPRESSION_H
#define MYCOMPILLER_LOGICOREXPRESSION_H
#include <BinaryExpression.h>

class LogicOrExpression : public BinaryExpression {
 public:
  using BinaryExpression::BinaryExpression;
  void AcceptVisitor(BaseASTVisitor*);
};

#endif  // MYCOMPILLER_LOGICOREXPRESSION_H

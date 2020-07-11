
#ifndef MYCOMPILLER_BINOPEXPRESSION_H
#define MYCOMPILLER_BINOPEXPRESSION_H

#include <BinOperatorType.h>
#include "IRExpression.h"

namespace ir_tree {

class BinOpExpression : public IRExpression {
 public:
  BinOpExpression(BinOperatorType, IRExpression*, IRExpression*);
  void AcceptVisitor(BaseIRVisitor*) override;

 public:
  BinOperatorType type_;
  IRExpression* first_;
  IRExpression* second_;
};

} // namespace ir_tree

#endif  // MYCOMPILLER_BINOPEXPRESSION_H

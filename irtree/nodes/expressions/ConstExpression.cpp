
#include "ConstExpression.h"
int ir_tree::ConstExpression::Value() {
  return value_;
}

ir_tree::ConstExpression::ConstExpression(int value) : value_(value) {
}

void ir_tree::ConstExpression::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

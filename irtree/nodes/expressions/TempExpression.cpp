
#include "TempExpression.h"
ir_tree::TempExpression::TempExpression(const ir_tree::Temp& temp)
    : temp_(temp) {
}

void ir_tree::TempExpression::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

ir_tree::IRNodeType ir_tree::TempExpression::GetType() {
  return IRNodeType::Temp;
}

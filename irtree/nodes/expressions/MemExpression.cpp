
#include "MemExpression.h"

ir_tree::MemExpression::MemExpression(IRExpression* expression)
    : expression_(expression) {
}

void ir_tree::MemExpression::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

ir_tree::IRNodeType ir_tree::MemExpression::GetType() {
  return IRNodeType::Mem;
}

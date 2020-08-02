
#include "AllocExpression.h"
ir_tree::AllocExpression::AllocExpression(size_t size) : size_(size) {
}

void ir_tree::AllocExpression::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}
ir_tree::IRNodeType ir_tree::AllocExpression::GetType() {
  return IRNodeType::Alloc;
}

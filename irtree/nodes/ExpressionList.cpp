
#include "ExpressionList.h"
ir_tree::ExpressionList::ExpressionList(std::vector<IRExpression*> expressions)
    : expressions_(expressions) {
}
void ir_tree::ExpressionList::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

ir_tree::IRNodeType ir_tree::ExpressionList::GetType() {
  return IRNodeType::ExpList;
}
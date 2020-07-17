
#include "NameExpression.h"
ir_tree::NameExpression::NameExpression(ir_tree::Label label) : label_(label) {
}

void ir_tree::NameExpression::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

ir_tree::IRNodeType ir_tree::NameExpression::GetType() {
  return IRNodeType::Name;
}

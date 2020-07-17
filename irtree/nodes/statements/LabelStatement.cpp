
#include "LabelStatement.h"
ir_tree::LabelStatement::LabelStatement(ir_tree::Label label) : label_(label) {
}

void ir_tree::LabelStatement::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

ir_tree::IRNodeType ir_tree::LabelStatement::GetType() {
  return IRNodeType::Label;
}

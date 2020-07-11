
#include "JumpConditionalStatement.h"
ir_tree::JumpConditionalStatement::JumpConditionalStatement(
    ir_tree::LogicOperatorType op, ir_tree::IRExpression* left,
    ir_tree::IRExpression* right, ir_tree::Label ltrue, ir_tree::Label lfalse)
    : operator_(op),
      left_(left),
      right_(right),
      label_true_(ltrue),
      label_false_(lfalse) {
}

void ir_tree::JumpConditionalStatement::AcceptVisitor(
    ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

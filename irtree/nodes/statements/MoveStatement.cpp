
#include "MoveStatement.h"
ir_tree::MoveStatement::MoveStatement(ir_tree::IRExpression* source,
                                      ir_tree::IRExpression* target)
    : source_(source), destination_(target) {
}

void ir_tree::MoveStatement::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

ir_tree::IRNodeType ir_tree::MoveStatement::GetType() {
  return IRNodeType::Move;
}

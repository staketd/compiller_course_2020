
#include "JumpStatement.h"
ir_tree::JumpStatement::JumpStatement(ir_tree::Label label) : label_(label) {
}

void ir_tree::JumpStatement::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

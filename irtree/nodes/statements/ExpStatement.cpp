
#include "ExpStatement.h"
ir_tree::ExpStatement::ExpStatement(ir_tree::IRExpression* expression)
    : expression_(expression) {
}

void ir_tree::ExpStatement::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

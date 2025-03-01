
#include "IRPrintStatement.h"
ir_tree::IRPrintStatement::IRPrintStatement(ir_tree::IRExpression* expression)
    : expression_(expression) {
}

void ir_tree::IRPrintStatement::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

ir_tree::IRNodeType ir_tree::IRPrintStatement::GetType() {
  return IRNodeType::Print;
}

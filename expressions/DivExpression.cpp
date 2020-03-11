#include "DivExpression.h"

int DivExpression::eval() const {
    return first_->eval() / second_->eval();
}

DivExpression::DivExpression(Expression* first, Expression* second): first_(first), second_(second) {}

void DivExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

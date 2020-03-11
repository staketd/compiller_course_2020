#include "MulExpression.h"

int MulExpression::eval() const {
    return first_->eval() * second_->eval();
}

MulExpression::MulExpression(Expression* fisrt, Expression* second): first_(fisrt), second_(second)  {}

void MulExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

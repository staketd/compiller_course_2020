#include "SubstractExpression.h"

int SubstractExpression::eval() const {
    return first_->eval() - second_->eval();
}

SubstractExpression::SubstractExpression(Expression* first, Expression* second): first_(first), second_(second) {}

void SubstractExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

#include "NumExpression.h"

int NumExpression::eval() const {
    return value_;
}

NumExpression::NumExpression(int value): value_(value) {}


void NumExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

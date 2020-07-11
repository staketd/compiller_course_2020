#include "NumExpression.h"

NumExpression::NumExpression(int value): value_(value) {}

void NumExpression::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

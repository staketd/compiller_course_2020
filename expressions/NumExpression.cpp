#include "NumExpression.h"

NumExpression::NumExpression(int value): value_(value) {}

void NumExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

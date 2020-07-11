
#include "GreaterOrEqualExpression.h"

void GreaterOrEqualExpression::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

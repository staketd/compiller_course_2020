
#include "LessOrEqualExpression.h"

void LessOrEqualExpression::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

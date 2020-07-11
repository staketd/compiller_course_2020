
#include "EqualExpression.h"

void EqualExpression::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

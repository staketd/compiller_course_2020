
#include "GreaterExpression.h"

void GreaterExpression::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

#include "MulExpression.h"

void MulExpression::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

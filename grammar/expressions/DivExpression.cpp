#include "DivExpression.h"

void DivExpression::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

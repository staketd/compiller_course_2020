
#include "LessExpression.h"

void LessExpression::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

#include "SubstractExpression.h"

void SubstractExpression::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

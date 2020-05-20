
#include "GreaterOrEqualExpression.h"

void GreaterOrEqualExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}


#include "LessOrEqualExpression.h"

void LessOrEqualExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}


#include "EqualExpression.h"

void EqualExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

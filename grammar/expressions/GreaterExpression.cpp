
#include "GreaterExpression.h"

void GreaterExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

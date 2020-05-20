#include "MulExpression.h"

void MulExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

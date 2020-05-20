#include "DivExpression.h"

void DivExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

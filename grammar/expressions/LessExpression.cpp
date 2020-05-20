
#include "LessExpression.h"

void LessExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

#include "SubstractExpression.h"

void SubstractExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

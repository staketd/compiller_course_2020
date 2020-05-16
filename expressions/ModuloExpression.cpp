
#include "ModuloExpression.h"

void ModuloExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

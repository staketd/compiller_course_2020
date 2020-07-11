
#include "ModuloExpression.h"

void ModuloExpression::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

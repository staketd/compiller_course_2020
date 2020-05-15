
#include "Scope.h"

Scope::Scope(StatementList* statements) : statements_(statements) {
}

void Scope::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

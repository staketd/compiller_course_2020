
#include "Scope.h"

Scope::Scope(StatementList* statements) : statements_(statements) {
}

void Scope::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

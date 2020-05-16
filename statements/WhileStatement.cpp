
#include "WhileStatement.h"

WhileStatement::WhileStatement(Expression* expression, Scope* scope)
        : check_expression_(expression), scope_(scope) {
}

void WhileStatement::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

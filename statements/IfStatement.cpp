
#include "IfStatement.h"

IfStatement::IfStatement(Expression* expr, StatementList* statements)
        : ifExpression_(expr), statements_(statements) {
}

void IfStatement::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

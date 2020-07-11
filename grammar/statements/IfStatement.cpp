
#include "IfStatement.h"

IfStatement::IfStatement(Expression* expr, Scope* then, Scope* s_else)
        : ifExpression_(expr), then_(then), else_(s_else) {
}

void IfStatement::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

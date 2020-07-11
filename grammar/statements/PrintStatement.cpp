#include "PrintStatement.h"

#include <utility>

PrintStatement::PrintStatement(Expression* expr) : expr_(expr) {
}

void PrintStatement::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

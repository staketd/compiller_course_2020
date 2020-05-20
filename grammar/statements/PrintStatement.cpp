#include "PrintStatement.h"

#include <utility>

PrintStatement::PrintStatement(Expression* expr) : expr_(expr) {
}

void PrintStatement::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

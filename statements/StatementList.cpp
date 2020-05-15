#include "StatementList.h"

void StatementList::AddStatement(Statement* statement) {
    statements_.push_back(statement);
}

void StatementList::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

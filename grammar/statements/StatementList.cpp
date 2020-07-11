#include "StatementList.h"

void StatementList::AddStatement(Statement* statement) {
    statements_.push_back(statement);
}

void StatementList::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

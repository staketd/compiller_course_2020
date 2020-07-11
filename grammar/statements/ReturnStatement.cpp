
#include "ReturnStatement.h"
ReturnStatement::ReturnStatement(Expression* expression)
    : expression_(expression) {
}

void ReturnStatement::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}

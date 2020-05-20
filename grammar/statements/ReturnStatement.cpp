
#include "ReturnStatement.h"
ReturnStatement::ReturnStatement(Expression* expression)
    : expression_(expression) {
}

void ReturnStatement::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

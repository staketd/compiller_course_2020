
#include "FuncCallStatement.h"

void FuncCallStatement::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

FuncCallStatement::FuncCallStatement(FuncCallExpression* expression)
    : expression_(expression) {
}

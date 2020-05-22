
#include "MethodCallStmt.h"

void MethodCallStmt::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

MethodCallStmt::MethodCallStmt(MethodCallExpression* expression)
    : expression_(expression) {
}

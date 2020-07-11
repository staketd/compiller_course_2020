
#include "MethodCallStmt.h"

void MethodCallStmt::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}

MethodCallStmt::MethodCallStmt(MethodCallExpression* expression)
    : expression_(expression) {
}

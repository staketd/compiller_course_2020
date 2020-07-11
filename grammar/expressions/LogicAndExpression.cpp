
#include "LogicAndExpression.h"

void LogicAndExpression::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}

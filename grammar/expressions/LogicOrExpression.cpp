
#include "LogicOrExpression.h"

void LogicOrExpression::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}

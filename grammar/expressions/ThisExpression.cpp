
#include "ThisExpression.h"
void ThisExpression::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}


#include "ThisExpression.h"
void ThisExpression::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

#include "CallArgumentList.h"

void CallArgumentList::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

void CallArgumentList::AddArgument(Expression* expression) {
  arguments_.push_back(expression);
}

#include "CallArgumentList.h"

void CallArgumentList::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}

void CallArgumentList::AddArgument(Expression* expression) {
  arguments_.push_back(expression);
}

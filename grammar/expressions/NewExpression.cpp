
#include "NewExpression.h"

NewExpression::NewExpression(const std::string& type) : type_(type) {
}

void NewExpression::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}

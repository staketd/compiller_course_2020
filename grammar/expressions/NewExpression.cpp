
#include "NewExpression.h"

NewExpression::NewExpression(const std::string& type) : type_(type) {
}

void NewExpression::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

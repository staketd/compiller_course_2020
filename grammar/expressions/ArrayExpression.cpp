
#include "ArrayExpression.h"
ArrayExpression::ArrayExpression(const std::string& name,
                                 Expression* expression)
    : name_(name), expression_(expression) {
}

void ArrayExpression::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}

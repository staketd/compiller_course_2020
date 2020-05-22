
#include "MethodCallExpression.h"
MethodCallExpression::MethodCallExpression(Expression* expression,
                                           const std::string& name,
                                           CallArgumentList* arguments)
    :expression_(expression), name_(name), arguments_(arguments) {
}

void MethodCallExpression::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

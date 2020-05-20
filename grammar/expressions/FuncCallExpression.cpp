
#include "FuncCallExpression.h"
FuncCallExpression::FuncCallExpression(const std::string& name,
                                       CallArgumentList* arguments)
    : name_(name), arguments_(arguments) {
}

void FuncCallExpression::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

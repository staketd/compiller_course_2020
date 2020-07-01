
#include "ArrayAssignment.h"

void ArrayAssignment::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

ArrayAssignment::ArrayAssignment(const std::string& name, Expression* ind,
                                 Expression* expr)
    : array_name_(name), ind_expression_(ind), expression_(expr) {
}

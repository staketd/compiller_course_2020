#include "IdentExpression.h"
#include <utility>

int IdentExpression::eval() const {
    return 0;
}

IdentExpression::IdentExpression(std::string ident): ident_(std::move(ident)) {}

void IdentExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

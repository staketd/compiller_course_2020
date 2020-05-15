#include "IdentExpression.h"
#include <utility>

IdentExpression::IdentExpression(std::string ident): ident_(std::move(ident)) {}

void IdentExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

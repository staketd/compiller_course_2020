#include "IdentExpression.h"
#include <utility>

IdentExpression::IdentExpression(std::string ident): name_(std::move(ident)) {}

void IdentExpression::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

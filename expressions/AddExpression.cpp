//
// Created by staket on 09.03.2020.
//

#include "AddExpression.h"

int AddExpression::eval() const {
    return first_->eval() + second_->eval();
}

AddExpression::AddExpression(Expression *first, Expression *second): first_(first), second_(second) {}

void AddExpression::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

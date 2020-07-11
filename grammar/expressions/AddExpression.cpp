//
// Created by staket on 09.03.2020.
//

#include "AddExpression.h"

void AddExpression::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

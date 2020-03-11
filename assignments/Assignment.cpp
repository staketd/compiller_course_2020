
#include "Assignment.h"

Assignment::Assignment(std::string variable, Expression* expression) : variable_(std::move(variable)),
                                                                       expression_(expression) {}

void Assignment::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}


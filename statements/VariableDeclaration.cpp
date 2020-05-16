
#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration(std::string name) : name_(std::move(name)) {
}

void VariableDeclaration::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}



#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration(std::string name,
                                         std::string type_name,
                                         Expression* expression)
    : type_name_(std::move(type_name)),
      name_(std::move(name)),
      expression_(expression) {
}

void VariableDeclaration::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}

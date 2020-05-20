
#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration(std::string name,
                                         std::string type_name)
    :type_name_(std::move(type_name)), name_(std::move(name)) {
}

void VariableDeclaration::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

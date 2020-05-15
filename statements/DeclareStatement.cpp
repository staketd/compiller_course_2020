
#include "DeclareStatement.h"

DeclareStatement::DeclareStatement(std::string name) : name_(std::move(name)) {
}

void DeclareStatement::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}


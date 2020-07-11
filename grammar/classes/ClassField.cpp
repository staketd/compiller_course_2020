#include "ClassField.h"

ClassField::ClassField(const std::string& type, const std::string& name)
    : type_(type), name_(name) {
}

void ClassField::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}

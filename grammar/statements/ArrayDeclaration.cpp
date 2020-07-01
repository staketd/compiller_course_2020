
#include "ArrayDeclaration.h"
ArrayDeclaration::ArrayDeclaration(const std::string& type,
                                   const std::string& name, size_t size)
    : size_(size), array_type_(type), name_(name) {
}

void ArrayDeclaration::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

#include "Class.h"

Class::Class(const std::string& name, ClassBody* body)
    : name_(name), body_(body) {
}

void Class::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

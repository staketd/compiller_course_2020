#include "VoidType.h"

VoidType::VoidType() : BaseType(Type::Void) {
}

std::string VoidType::TypeName() {
  return "void";
}

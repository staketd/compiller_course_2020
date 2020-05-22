
#include "BoolType.h"

BoolType::BoolType() : BaseType(Type::Bool) {
}

std::string BoolType::TypeName() {
  return "Bool";
}

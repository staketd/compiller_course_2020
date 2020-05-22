
#include "IntegerType.h"

IntegerType::IntegerType() : BaseType(Type::Integer) {
}

std::string IntegerType::TypeName() {
  return "Integer";
}

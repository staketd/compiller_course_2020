
#include "ArrayType.h"

ArrayType::ArrayType(std::shared_ptr<BaseType> type)
    : BaseType(Type::Array), array_type_(type) {
}

std::string ArrayType::TypeName() {
  return array_type_->TypeName();
}

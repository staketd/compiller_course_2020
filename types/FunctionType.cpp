#include "FunctionType.h"

FunctionType::FunctionType(std::shared_ptr<BaseType> return_type)
    : BaseType(Type::Function), return_type_(return_type) {
}
std::string FunctionType::TypeName() {
  return "Function";
}

std::shared_ptr<BaseType> FunctionType::GetReturnType() {
  return return_type_;
}

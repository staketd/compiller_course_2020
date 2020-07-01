
#include "BaseType.h"

BaseType::BaseType(BaseType::Type type) : type_(type) {
}

bool BaseType::IsBool() {
  return type_ == Type::Bool;
}

bool BaseType::IsInteger() {
  return type_ == Type::Integer;
}

bool BaseType::IsClass() {
  return type_ == Type::Class;
}

bool BaseType::IsFunction() {
  return type_ == Type::Function;
}

bool BaseType::IsVoid() {
  return type_ == Type::Void;
}

bool BaseType::IsSameWith(std::shared_ptr<BaseType> other) {
  return type_ == other->type_;
}

bool BaseType::IsArray() {
  return type_ == Type::Array;
}

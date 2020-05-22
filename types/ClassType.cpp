
#include "ClassType.h"

ClassType::ClassType(const std::string& name)
    : BaseType(Type::Class), class_name_(name) {
}

bool ClassType::IsSameWith(std::shared_ptr<BaseType> other) {
  if (type_ != other->type_) {
    return false;
  }
  auto other_class = std::dynamic_pointer_cast<ClassType>(other);
  return other_class != nullptr && class_name_ == other_class->class_name_;
}

std::string ClassType::TypeName() {
  return class_name_;
}

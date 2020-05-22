#ifndef MYCOMPILLER_TYPESSUPPORT_CPP
#define MYCOMPILLER_TYPESSUPPORT_CPP

#include <IntegerType.h>
#include <BoolType.h>
#include <VoidType.h>
#include <ClassType.h>


inline std::shared_ptr<BaseType> CreateTypePtr(const std::string type_name) {
  if (type_name == "Integer") {
    return std::make_shared<IntegerType>();
  } else if (type_name == "Bool") {
    return std::make_shared<BoolType>();
  } else if (type_name == "void") {
    return std::make_shared<VoidType>();
  }
  return std::make_shared<ClassType>(type_name);
}

inline bool IsConvertible(std::shared_ptr<BaseType> first_type,
                   std::shared_ptr<BaseType> second_type) {
  return (first_type->IsInteger() || first_type->IsBool()) &&
                (second_type->IsInteger() || second_type->IsBool());
}

inline bool IsPrimitiveType(const std::string& type) {
  return type == "Integer" || type == "Bool";
}

#endif


#include "Function.h"
#include <Integer.h>
#include <BoolType.h>

BaseType* CreateType(const std::string type_name) {
  if (type_name == "Integer") {
    return new Integer();
  } else if (type_name == "Bool") {
    return new BoolType();
  }
  return nullptr;
}

Function::Function(const std::string& name, FuncArgumentList* args,
                   StatementList* statements, const std::string& type)
    : name_(name),
      arguments_(args),
      statements_(statements),
      return_type_(CreateType(type)) {
}

void Function::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

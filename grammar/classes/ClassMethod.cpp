
#include "ClassMethod.h"
#include <Integer.h>
#include <BoolObject.h>

ClassMethod::ClassMethod(const std::string& name, MethodArgumentList* args,
                   StatementList* statements, const std::string& type)
    : name_(name),
      arguments_(args),
      statements_(statements),
      return_type_(type) {
}

void ClassMethod::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

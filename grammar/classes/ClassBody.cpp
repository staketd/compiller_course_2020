
#include "ClassBody.h"

void ClassBody::AddMethod(ClassMethod* function) {
  methods_.push_back(function);
}

void ClassBody::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

void ClassBody::AddField(ClassField* field) {
  fields_.push_back(field);
}

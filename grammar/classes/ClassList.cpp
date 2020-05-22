
#include "ClassList.h"
void ClassList::AddClass(Class* class_decl) {
  classes_.push_back(class_decl);
}

void ClassList::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}


#include "MethodArgumentList.h"
void MethodArgumentList::AddArgument(const std::string& type,
                                     const std::string& name) {
  types_.push_back(type);
  names_.push_back(name);
}

void MethodArgumentList::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}

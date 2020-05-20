
#include "FuncArgumentList.h"
void FuncArgumentList::AddArgument(const std::string& name) {
  names_.push_back(name);
}

void FuncArgumentList::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

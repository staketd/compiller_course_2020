
#include "FunctionList.h"

void FunctionList::AddFunction(Function* function) {
  functions_.push_back(function);
}

void FunctionList::AcceptVisitor(BaseVisitor* visitor) {
  visitor->Visit(this);
}

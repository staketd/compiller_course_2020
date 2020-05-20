#include "Program.h"

Program::Program(FunctionList* functions) : functions_(functions) {}

void Program::AcceptVisitor(BaseVisitor* visitor) {
  functions_->AcceptVisitor(visitor);
}

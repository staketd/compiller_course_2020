#include "Program.h"

Program::Program(ClassMain* main, ClassList* list)
    : main_(main), classes_(list) {
}

void Program::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}

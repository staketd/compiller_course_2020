#include "Program.h"

Program::Program(StatementList* statements) : statements_(statements) {}

void Program::AcceptVisitor(BaseVisitor* visitor) {
    statements_->AcceptVisitor(visitor);
}


#include "ReadStatement.h"

ReadStatement::ReadStatement(std::string var) : variable_(std::move(var)) {
}

void ReadStatement::AcceptVisitor(BaseASTVisitor* visitor) {
    visitor->Visit(this);
}

std::string ReadStatement::GetVariableName() const {
    return variable_;
}



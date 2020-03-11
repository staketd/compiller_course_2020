#include "AssignmentList.h"

void AssignmentList::AddAssignment(Assignment* assignment) {
    assignments_.push_back(assignment);
}

void AssignmentList::AcceptVisitor(BaseVisitor* visitor) {
    visitor->Visit(this);
}

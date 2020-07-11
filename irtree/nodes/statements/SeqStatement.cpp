
#include "SeqStatement.h"

ir_tree::SeqStatement::SeqStatement(ir_tree::IRStatement* first,
                                    ir_tree::IRStatement* second)
    : first_(first), second_(second) {
}

void ir_tree::SeqStatement::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

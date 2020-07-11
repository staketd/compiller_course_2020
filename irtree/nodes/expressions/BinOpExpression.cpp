
#include "BinOpExpression.h"
ir_tree::BinOpExpression::BinOpExpression(ir_tree::BinOperatorType type,
                                          IRExpression* first,
                                          IRExpression* second)
    : type_(type), first_(first), second_(second) {
}

void ir_tree::BinOpExpression::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

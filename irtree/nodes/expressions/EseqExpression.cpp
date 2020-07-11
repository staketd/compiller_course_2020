
#include "EseqExpression.h"
ir_tree::EseqExpression::EseqExpression(ir_tree::IRStatement* statement,
                                        ir_tree::IRExpression* expression)
    : statement_(statement), expression_(expression) {
}

void ir_tree::EseqExpression::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

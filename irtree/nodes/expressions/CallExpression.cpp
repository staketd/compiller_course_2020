
#include "CallExpression.h"

ir_tree::CallExpression::CallExpression(ir_tree::IRExpression* name,
                                        ir_tree::ExpressionList* args)
    : function_name_(name), args_(args) {
}

void ir_tree::CallExpression::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}


#include "CallExpression.h"

ir_tree::CallExpression::CallExpression(ir_tree::IRExpression* name,
                                        ir_tree::ExpressionList* args,
                                        bool has_return_value)
    : function_name_(name), args_(args), has_return_value_(has_return_value) {
}

void ir_tree::CallExpression::AcceptVisitor(ir_tree::BaseIRVisitor* visitor) {
  visitor->Visit(this);
}

ir_tree::IRNodeType ir_tree::CallExpression::GetType() {
  return IRNodeType::Call;
}

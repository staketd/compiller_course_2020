
#include "CompareConditionalWrapper.h"
#include <JumpConditionalStatement.h>
ir_tree::CompareConditionalWrapper::CompareConditionalWrapper(
    ir_tree::LogicOperatorType op, ir_tree::IRExpression* first,
    ir_tree::IRExpression* second)
    : operator_(op), first_(first), second_(second) {
}
ir_tree::IRStatement* ir_tree::CompareConditionalWrapper::ToConditional(
    ir_tree::Label true_label, ir_tree::Label false_label) {
  return new JumpConditionalStatement(operator_, first_, second_, true_label,
                                      false_label);
}


#include "NegateConditionalWrapper.h"
ir_tree::NegateConditionalWrapper::NegateConditionalWrapper(
    ir_tree::SubtreeWrapper* wrapper) : wrapper_(wrapper) {
}

ir_tree::IRStatement* ir_tree::NegateConditionalWrapper::ToConditional(
    ir_tree::Label true_label, ir_tree::Label false_label) {
  return wrapper_->ToConditional(false_label, true_label);
}

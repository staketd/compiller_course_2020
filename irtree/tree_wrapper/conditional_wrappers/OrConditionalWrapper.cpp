
#include "OrConditionalWrapper.h"
#include <SeqStatement.h>
#include <LabelStatement.h>
ir_tree::OrConditionalWrapper::OrConditionalWrapper(
    ir_tree::SubtreeWrapper* first, ir_tree::SubtreeWrapper* second)
    : first_(first), second_(second) {
}
ir_tree::IRStatement* ir_tree::OrConditionalWrapper::ToConditional(
    ir_tree::Label true_label,
    ir_tree::Label false_label
    ) {
  Label middle_label;

  return new SeqStatement(
      first_->ToConditional(true_label, middle_label),
      new SeqStatement(
          new LabelStatement(middle_label),
          second_->ToConditional(true_label, false_label)
          )
      );
}


#include "FrameAddress.h"
#include <BinOperatorType.h>
#include <ConstExpression.h>
#include <BinOpExpression.h>
#include <MemExpression.h>

ir_tree::FrameAddress::FrameAddress(ir_tree::Address* frame, int offset)
    : frame_addres_(frame), offset_(offset) {
}

ir_tree::IRExpression* ir_tree::FrameAddress::ToExpression() {
  IRExpression* offset_expression;
  if (offset_ != 0) {
    BinOperatorType type = BinOperatorType::PLUS;
    int value = offset_;
    if (offset_ < 0) {
      type = BinOperatorType::MINUS;
      value = -offset_;
    }
    offset_expression = new ir_tree::BinOpExpression(
        type, frame_addres_->ToExpression(),
        new ConstExpression(value));
  } else {
    offset_expression = frame_addres_->ToExpression();
  }
  return new MemExpression(offset_expression);
}


#include "Block.h"

ir_tree::Block::Block() : last_block_(false), label_(nullptr), jump_(nullptr) {
}

ir_tree::LabelStatement* ir_tree::Block::GetLabel() {
  return label_;
}

ir_tree::IRStatement* ir_tree::Block::GetJump() {
  return jump_;
}

void ir_tree::Block::AddStatement(ir_tree::IRStatement* stmt) {
  statements_.push_back(stmt);
}

void ir_tree::Block::SetLabel(ir_tree::LabelStatement* statement) {
  label_ = statement;
}

void ir_tree::Block::SetJump(ir_tree::JumpConditionalStatement* statement) {
  jump_ = statement;
}

void ir_tree::Block::SetJump(ir_tree::JumpStatement* statement) {
  jump_ = statement;
}

std::vector<ir_tree::IRStatement*>& ir_tree::Block::GetStatements() {
  return statements_;
}


#include "Trace.h"

void ir_tree::Trace::AddBlock(const ir_tree::Block& block) {
  blocks_.push_back(block);
}

std::vector<ir_tree::Block>& ir_tree::Trace::GetBlocks() {
  return blocks_;
}

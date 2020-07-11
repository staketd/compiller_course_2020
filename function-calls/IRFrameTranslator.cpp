
#include "IRFrameTranslator.h"
#include <FrameAddress.h>
#include <RegAddress.h>

const std::string ir_tree::IRFrameTranslator::kReturnAddress = "::return";
const std::string ir_tree::IRFrameTranslator::kFramePointerAddress = "::fp";
const std::string ir_tree::IRFrameTranslator::kReturnValueAddress =
    "::return_value";
const int ir_tree::IRFrameTranslator::kWordSize = 4;

void ir_tree::IRFrameTranslator::AddVariable(Symbol symb, int offset) {
  scopes_symbols_stack_.push_back(symb);
  if (addresses_.find(symb) == addresses_.end()) {
    addresses_[symb];
  }
  addresses_[symb].push_back(new FrameAddress(FramePointer(), offset));
}

ir_tree::Address* ir_tree::IRFrameTranslator::FramePointer() {
  return addresses_[Symbol(kFramePointerAddress)].back();
}

void ir_tree::IRFrameTranslator::AddLocalVariable(const Symbol& symbol,
                                                  size_t size) {
  AddVariable(symbol, local_offset_);
  local_offset_ += size;
}

ir_tree::Address* ir_tree::IRFrameTranslator::GetAddress(const Symbol& symbol) {
  return addresses_[symbol].back();
}

void ir_tree::IRFrameTranslator::AddArgument(const Symbol& symbol,
                                             size_t size) {
  AddVariable(symbol, arg_offset_);
  arg_offset_ -= kWordSize;
}
ir_tree::IRFrameTranslator::IRFrameTranslator(const Symbol& symbol)
    : function_name_(symbol),
      local_offset_(kWordSize),
      arg_offset_(-kWordSize) {
  addresses_[Symbol(kFramePointerAddress)].push_back(
      new RegAddress(Temp(kFramePointerAddress)));

  addresses_[Symbol(kReturnValueAddress)].push_back(
      new RegAddress(Temp(kReturnValueAddress)));
}

ir_tree::Address* ir_tree::IRFrameTranslator::GetReturnValueAddress() {
  return addresses_[Symbol(kReturnValueAddress)].back();
}

void ir_tree::IRFrameTranslator::AddReturnAddress() {
  AddVariable(Symbol(kReturnAddress), 0);
}

void ir_tree::IRFrameTranslator::BeginScope() {
  scopes_symbols_stack_.push_back(Symbol("{"));
}

void ir_tree::IRFrameTranslator::EndScope() {
  while (scopes_symbols_stack_.back() != Symbol("{")) {
    auto top_symbol = scopes_symbols_stack_.back();
    scopes_symbols_stack_.pop_back();

    addresses_[top_symbol].pop_back();
    local_offset_ -= kWordSize;
    if (addresses_[top_symbol].empty()) {
      addresses_.erase(top_symbol);
    }
  }
  scopes_symbols_stack_.pop_back();
}

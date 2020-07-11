
#include "RegAddress.h"
#include <TempExpression.h>
ir_tree::RegAddress::RegAddress(const ir_tree::Temp& temp) : temp_(temp) {
}

ir_tree::IRExpression* ir_tree::RegAddress::ToExpression() {
  return new TempExpression(temp_);
}

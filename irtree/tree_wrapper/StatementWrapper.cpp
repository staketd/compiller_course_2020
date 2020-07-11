
#include "StatementWrapper.h"
#include <macros.h>

ir_tree::StatementWrapper::StatementWrapper(ir_tree::IRStatement* statement)
    : statement_(statement) {
}

ir_tree::IRExpression* ir_tree::StatementWrapper::ToExpression() {
  UNREACHABLE("Cannot convert statement to expression");
}

ir_tree::IRStatement* ir_tree::StatementWrapper::ToStatement() {
  return statement_;
}

ir_tree::IRStatement* ir_tree::StatementWrapper::ToConditional(ir_tree::Label,
                                                             ir_tree::Label) {
  UNREACHABLE("Cannot create conditional from statement");
}

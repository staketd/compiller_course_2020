
#include "ExpressionWrapper.h"
#include <ExpStatement.h>
#include <LogicOperatorType.h>
#include <ConstExpression.h>
#include <JumpConditionalStatement.h>
ir_tree::ExpressionWrapper::ExpressionWrapper(ir_tree::IRExpression* expression)
    : expression_(expression) {
}

ir_tree::IRExpression* ir_tree::ExpressionWrapper::ToExpression() {
  return expression_;
}

ir_tree::IRStatement* ir_tree::ExpressionWrapper::ToStatement() {
  return new ExpStatement(expression_);
}

ir_tree::IRStatement* ir_tree::ExpressionWrapper::ToConditional(
    ir_tree::Label true_label, ir_tree::Label false_label) {
  return new JumpConditionalStatement(
      ir_tree::LogicOperatorType::NE,
      expression_,
      new ir_tree::ConstExpression(0),
      true_label,
      false_label
  );
}

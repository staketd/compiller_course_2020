
#include "EliminateDoubleCalls.h"
#include <sources.h>
void ir_tree::EliminateDoubleCalls::Visit(
    ir_tree::BinOpExpression* expression) {
  auto left = VisitAndReturnValue(expression->first_).expression_;
  auto right = VisitAndReturnValue(expression->second_).expression_;
  last_value_set_.expression_ = new BinOpExpression(
      expression->type_,
      left,
      right);
}

void ir_tree::EliminateDoubleCalls::Visit(ir_tree::CallExpression* expression) {
  auto args = VisitAndReturnValue(expression->args_).expression_list_;
  auto expr = VisitAndReturnValue(expression->function_name_).expression_;
  if (!expression->has_return_value_) {
    last_value_set_.expression_ = new CallExpression(expr, args, false);
    return;
  }
  Temp temp;
  last_value_set_.expression_ = new EseqExpression(
      new MoveStatement(
          new CallExpression(
              expr,
              args,
              true
              ),
          new TempExpression(temp)),
      new TempExpression(temp));
}

void ir_tree::EliminateDoubleCalls::Visit(
    ir_tree::ConstExpression* expression) {
  last_value_set_.expression_ = new ConstExpression(expression->Value());
}

void ir_tree::EliminateDoubleCalls::Visit(ir_tree::EseqExpression* expression) {
  last_value_set_.expression_ = new EseqExpression(
      VisitAndReturnValue(expression->statement_).statement_,
      VisitAndReturnValue(expression->expression_).expression_);
}

void ir_tree::EliminateDoubleCalls::Visit(ir_tree::MemExpression* expression) {
  last_value_set_.expression_ = new MemExpression(
      VisitAndReturnValue(expression->expression_).expression_);
}

void ir_tree::EliminateDoubleCalls::Visit(ir_tree::NameExpression* expression) {
  last_value_set_.expression_ = new NameExpression(expression->label_);
}

void ir_tree::EliminateDoubleCalls::Visit(ir_tree::TempExpression* expression) {
  last_value_set_.expression_ = new TempExpression(expression->temp_);
}

void ir_tree::EliminateDoubleCalls::Visit(ir_tree::ExpStatement* statement) {
  last_value_set_.statement_ = new ExpStatement(VisitAndReturnValue(statement->expression_).expression_);
}

void ir_tree::EliminateDoubleCalls::Visit(
    ir_tree::JumpStatement* jump_statement) {
  last_value_set_.statement_ = new JumpStatement(jump_statement->label_);
}

void ir_tree::EliminateDoubleCalls::Visit(
    ir_tree::JumpConditionalStatement* jump_conditional_statement) {
  auto left = VisitAndReturnValue(jump_conditional_statement->left_);
  auto right = VisitAndReturnValue(jump_conditional_statement->right_);

  last_value_set_.statement_ = new JumpConditionalStatement(
      jump_conditional_statement->operator_, left.expression_,
      right.expression_, jump_conditional_statement->label_true_,
      jump_conditional_statement->label_false_);
}

void ir_tree::EliminateDoubleCalls::Visit(ir_tree::LabelStatement* statement) {
  last_value_set_.statement_ = new LabelStatement(statement->label_);
}

void ir_tree::EliminateDoubleCalls::Visit(ir_tree::MoveStatement* statement) {
  last_value_set_.statement_ =
      new MoveStatement(
      VisitAndReturnValue(statement->source_).expression_,
      VisitAndReturnValue(statement->destination_).expression_);
}

void ir_tree::EliminateDoubleCalls::Visit(ir_tree::SeqStatement* statement) {
  last_value_set_.statement_ =
      new SeqStatement(VisitAndReturnValue(statement->first_).statement_,
                       VisitAndReturnValue(statement->second_).statement_);
}

void ir_tree::EliminateDoubleCalls::Visit(
    ir_tree::ExpressionList* expression_list) {
  for (auto& expression : expression_list->expressions_) {
    expression = VisitAndReturnValue(expression).expression_;
  }
  last_value_set_.expression_list_ =
      new ExpressionList(expression_list->expressions_);
}

void ir_tree::EliminateDoubleCalls::Visit(
    ir_tree::IRPrintStatement* statement) {
  last_value_set_.statement_ = new IRPrintStatement(
      VisitAndReturnValue(statement->expression_).expression_);
}

ir_tree::SubtreeWrapper* ir_tree::EliminateDoubleCalls::GetTree() {
  return new ir_tree::StatementWrapper(last_value_set_.statement_);
}

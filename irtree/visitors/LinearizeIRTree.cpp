
#include "LinearizeIRTree.h"
#include <sources.h>
#include <macros.h>

void ir_tree::LinearizeIRTree::Visit(ir_tree::BinOpExpression* expression) {
  auto first = VisitAndReturnValue(expression->first_).expression_;
  auto second = VisitAndReturnValue(expression->second_).expression_;

  last_value_set_.expression_ = new BinOpExpression(
      expression->type_, first, second);
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::CallExpression* expression) {
  auto expr = VisitAndReturnValue(expression->function_name_).expression_;
  auto args = VisitAndReturnValue(expression->args_).expression_list_;

  last_value_set_.expression_ =
      new CallExpression(expr, args, expression->has_return_value_);
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::ConstExpression* expression) {
  last_value_set_.expression_ = new ConstExpression(expression->Value());
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::EseqExpression* expression) {
  UNREACHABLE("Eseq found after eseq elimination")
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::MemExpression* expression) {
  auto expr = VisitAndReturnValue(expression->expression_).expression_;
  last_value_set_.expression_ = new MemExpression(expr);
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::NameExpression* expression) {
  last_value_set_.expression_ = new NameExpression(expression->label_);
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::TempExpression* expression) {
  last_value_set_.expression_ = new TempExpression(expression->temp_);
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::ExpStatement* statement) {
  auto expr = VisitAndReturnValue(statement->expression_).expression_;
  last_value_set_.statement_ = new ExpStatement(expr);
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::JumpStatement* statement) {
  last_value_set_.statement_ = new JumpStatement(statement->label_);
}

void ir_tree::LinearizeIRTree::Visit(
    ir_tree::JumpConditionalStatement* statement) {
  auto left = VisitAndReturnValue(statement->left_).expression_;
  auto right = VisitAndReturnValue(statement->right_).expression_;

  last_value_set_.statement_ = new JumpConditionalStatement(
      statement->operator_, left, right, statement->label_true_,
      statement->label_false_);
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::LabelStatement* statement) {
  last_value_set_.statement_ = new LabelStatement(statement->label_);
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::MoveStatement* statement) {
  auto src = VisitAndReturnValue(statement->source_).expression_;
  auto dst = VisitAndReturnValue(statement->destination_).expression_;

  last_value_set_.statement_ = new MoveStatement(src, dst);
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::SeqStatement* statement) {
  auto first = VisitAndReturnValue(statement->first_).statement_;
  if (first->GetType() == IRNodeType::Seq) {
    auto seq = dynamic_cast<SeqStatement*>(first);
    statement->second_ = new SeqStatement(seq->second_, statement->second_);
    first = seq->first_;
  }

  auto second = VisitAndReturnValue(statement->second_).statement_;

  last_value_set_.statement_ = new SeqStatement(first, second);
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::ExpressionList* list) {
  last_value_set_.expression_list_ = new ExpressionList(
      std::vector<IRExpression*>(list->expressions_.size(), nullptr));

  for (size_t i = 0; i < list->expressions_.size(); ++i) {
    last_value_set_.expression_list_->expressions_[i] =
        VisitAndReturnValue(list->expressions_[i]).expression_;
  }
}

void ir_tree::LinearizeIRTree::Visit(ir_tree::IRPrintStatement* statement) {
  auto expr = VisitAndReturnValue(statement->expression_).expression_;

  last_value_set_.statement_ = new IRPrintStatement(expr);
}

ir_tree::IRStatement* ir_tree::LinearizeIRTree::GetTree() {
  return last_value_set_.statement_;
}

std::vector<ir_tree::IRStatement*>
ir_tree::LinearizeIRTree::GetStatementList() {
  std::vector<IRStatement*> result;
  SeqStatement* now = dynamic_cast<SeqStatement*>(GetTree());
  while (true) {
    result.push_back(now->first_);
    if (now->first_->GetType() == IRNodeType::Seq) {
      UNREACHABLE("All left seqs must have been eliminated, but found one")
    }
    auto stmt = now->second_;
    now = dynamic_cast<SeqStatement*>(now->second_);
    if (now == nullptr) {
      result.push_back(stmt);
      break;
    }
  }
  return result;
}

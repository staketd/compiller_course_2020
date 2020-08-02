
#include "IRPrintVisitor.h"
#include <sources.h>

void ir_tree::IRPrintVisitor::Visit(ir_tree::BinOpExpression* expression) {
  PrintTabs();
  stream_ << "BinaryOperationExpression: ";
  switch (expression->type_) {
    case BinOperatorType::PLUS:
      stream_ << "PLUS";
      break;
    case BinOperatorType::MINUS:
      stream_ << "MINUS";
      break;
    case BinOperatorType::MUL:
      stream_ << "MUL";
      break;
    case BinOperatorType::DIV:
      stream_ << "DIV";
      break;
    case BinOperatorType::AND:
      stream_ << "AND";
      break;
    case BinOperatorType::OR:
      stream_ << "OR";
      break;
    case BinOperatorType::MOD:
      stream_ << "MOD";
      break;
  }
  stream_ << "\n";
  ++tabs_;
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
  --tabs_;
}

void ir_tree::IRPrintVisitor::PrintTabs() {
  for (size_t i = 0; i < tabs_; ++i) {
    stream_ << "\t";
  }
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::CallExpression* expression) {
  PrintTabs();
  stream_ << "CallExpresion:\n";
  ++tabs_;
  expression->function_name_->AcceptVisitor(this);
  expression->args_->AcceptVisitor(this);
  --tabs_;
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::ConstExpression* expression) {
  PrintTabs();
  stream_ << "ConstExpression: " << expression->Value() << "\n";
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::EseqExpression* expression) {
  PrintTabs();
  stream_ << "EseqExpression:\n";
  ++tabs_;
  expression->statement_->AcceptVisitor(this);
  expression->expression_->AcceptVisitor(this);
  --tabs_;
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::MemExpression* expression) {
  PrintTabs();
  stream_ << "MemExpression:\n";
  ++tabs_;
  expression->expression_->AcceptVisitor(this);
  --tabs_;
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::NameExpression* expression) {
  PrintTabs();

  stream_ << "NameExpression: " << expression->label_.ToString() << "\n";
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::TempExpression* expression) {
  PrintTabs();
  stream_ << "TempExpression: " << expression->temp_.ToString() << '\n';
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::ExpStatement* statement) {
  PrintTabs();
  stream_ << "ExpStatement:\n";
  ++tabs_;
  statement->expression_->AcceptVisitor(this);
  --tabs_;
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::JumpStatement* statement) {
  PrintTabs();
  stream_ << "JumpStatement: " + statement->label_.ToString() + "\n";
}

void ir_tree::IRPrintVisitor::Visit(
    ir_tree::JumpConditionalStatement* statement) {
  PrintTabs();
  stream_ << "JumpConditionalStatement: ";
  switch (statement->operator_) {
    case LogicOperatorType::LT:
      stream_ << "LT";
      break;
    case LogicOperatorType::GT:
      stream_ << "GT";
      break;
    case LogicOperatorType::LE:
      stream_ << "LE";
      break;
    case LogicOperatorType::GE:
      stream_ << "GE";
      break;
    case LogicOperatorType::EQ:
      stream_ << "EQ";
      break;
    case LogicOperatorType::NE:
      stream_ << "NE";
      break;
  }
  stream_ << "\n";
  ++tabs_;
  PrintTabs();
  stream_ << "TrueLabel: " + statement->label_true_.ToString() + "\n";
  PrintTabs();
  stream_ << "FalseLabel: " + statement->label_false_.ToString() + "\n";
  statement->left_->AcceptVisitor(this);
  statement->right_->AcceptVisitor(this);
  --tabs_;
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::LabelStatement* statement) {
  PrintTabs();
  stream_ << "LabelStatement: " + statement->label_.ToString() + "\n";
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::MoveStatement* statement) {
  PrintTabs();
  stream_ << "MoveStatement:\n";
  ++tabs_;
  statement->destination_->AcceptVisitor(this);
  statement->source_->AcceptVisitor(this);
  --tabs_;
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::SeqStatement* statement) {
  PrintTabs();
  stream_ << "SeqStatement: \n";
  ++tabs_;
  statement->first_->AcceptVisitor(this);
  statement->second_->AcceptVisitor(this);
  -tabs_;
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::ExpressionList* list) {
  PrintTabs();
  stream_ << "ExpressionList:\n";
  ++tabs_;
  for (auto expr : list->expressions_) {
    expr->AcceptVisitor(this);
  }
  --tabs_;
}
ir_tree::IRPrintVisitor::IRPrintVisitor(std::ofstream& stream)
    : stream_(stream), tabs_(0) {
}

void ir_tree::IRPrintVisitor::Visit(IRPrintStatement* stmt) {
  PrintTabs();
  stream_ << "PrintStatement:\n";
  ++tabs_;
  stmt->expression_->AcceptVisitor(this);
  --tabs_;
}

void ir_tree::IRPrintVisitor::Visit(ir_tree::AllocExpression* expression) {
  PrintTabs();
  stream_ << "AllocExpression :" << expression->size_ << "\n";
}


#include <iostream>
#include "Interprenter.h"

#include "sources.h"
#include <Integer.h>

void Interprenter::Visit(StatementList* statements) {
  for (auto statement : statements->statements_) {
    statement->AcceptVisitor(this);
  }
}

void Interprenter::Visit(Assignment* assignment) {
  auto value =
      std::make_shared<Integer>(VisitAndSetValue(assignment->expression_));
  current_layer_->SetValue(Symbol(assignment->variable_), value);
}

void Interprenter::Visit(AddExpression* add_expression) {
  last_value_set_ = VisitAndSetValue(add_expression->first_) +
                    VisitAndSetValue(add_expression->second_);
}

void Interprenter::Visit(MulExpression* expression) {
  last_value_set_ = VisitAndSetValue(expression->first_) *
                    VisitAndSetValue(expression->second_);
}

void Interprenter::Visit(DivExpression* expression) {
  last_value_set_ = VisitAndSetValue(expression->first_) /
                    VisitAndSetValue(expression->second_);
}

void Interprenter::Visit(SubstractExpression* expression) {
  last_value_set_ = VisitAndSetValue(expression->first_) -
                    VisitAndSetValue(expression->second_);
}

void Interprenter::Visit(IdentExpression* expression) {
  last_value_set_ =
      current_layer_->GetValue(Symbol(expression->ident_))->ToInt();
}

void Interprenter::Visit(NumExpression* expression) {
  last_value_set_ = expression->value_;
}

void Interprenter::Visit(Program* program) {
  program->AcceptVisitor(this);
}

void Interprenter::ExecuteCode(Program* program) {
  Visit(program);
}

void Interprenter::Visit(PrintStatement* print) {
  std::cout << VisitAndSetValue(print->expr_) << std::endl;
}

void Interprenter::Visit(ReadStatement* read) {
  std::cin >> last_value_set_;
  auto value = std::make_shared<Integer>(last_value_set_);
  current_layer_->SetValue(Symbol(read->GetVariableName()), value);
}

void Interprenter::Visit(EqualExpression* eq) {
  last_value_set_ =
      (VisitAndSetValue(eq->first_) == VisitAndSetValue(eq->second_));
}

void Interprenter::Visit(LessExpression* less) {
  last_value_set_ =
      (VisitAndSetValue(less->first_) < VisitAndSetValue(less->second_));
}

void Interprenter::Visit(GreaterExpression* expr) {
  last_value_set_ =
      (VisitAndSetValue(expr->first_) > VisitAndSetValue(expr->second_));
}

void Interprenter::Visit(LessOrEqualExpression* expr) {
  last_value_set_ =
      (VisitAndSetValue(expr->first_) <= VisitAndSetValue(expr->second_));
}

void Interprenter::Visit(GreaterOrEqualExpression* expr) {
  last_value_set_ =
      (VisitAndSetValue(expr->first_) >= VisitAndSetValue(expr->first_));
}

void Interprenter::Visit(IfStatement* if_statement) {
  if (VisitAndSetValue(if_statement->ifExpression_)) {
    if_statement->then_->AcceptVisitor(this);
  } else if (if_statement->else_ != nullptr) {
    if_statement->else_->AcceptVisitor(this);
  }
}

void Interprenter::Visit(Scope* scope) {
  current_layer_ = current_layer_->GetChildren(current_children_.back());
  current_children_.push_back(0);

  scope->statements_->AcceptVisitor(this);

  current_children_.pop_back();
  current_children_.back()++;
  current_layer_ = current_layer_->GetParent();
}

void Interprenter::Visit(VariableDeclaration* decl) {
  current_layer_->IncreaseOffset();
}

Interprenter::Interprenter(ScopeLayer* main_scope)
    : current_layer_(main_scope), current_children_({0}) {
}

void Interprenter::Visit(ModuloExpression* expression) {
  last_value_set_ = VisitAndSetValue(expression->first_) %
                    VisitAndSetValue(expression->second_);
}

void Interprenter::Visit(WhileStatement* statement) {
  while (VisitAndSetValue(statement->check_expression_)) {
    Visit(statement->scope_);
    current_children_.back()--;
  }
}

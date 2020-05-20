
#include "FunctionCallVisitor.h"
#include <sources.h>
#include <iostream>

void FunctionCallVisitor::Visit(StatementList* statements) {
  for (auto statement : statements->statements_) {
    statement->AcceptVisitor(this);
    if (returned_) {
      return;
    }
  }
}

void FunctionCallVisitor::Visit(Assignment* assignment) {
  VisitAndSetValue(assignment->expression_);
  SetValue(Symbol(assignment->variable_), last_value_set_);
}

void FunctionCallVisitor::Visit(AddExpression* add_expression) {
  last_value_set_ = VisitAndSetValue(add_expression->first_) +
                    VisitAndSetValue(add_expression->second_);
}

void FunctionCallVisitor::Visit(MulExpression* expression) {
  last_value_set_ = VisitAndSetValue(expression->first_) *
                    VisitAndSetValue(expression->second_);
}

void FunctionCallVisitor::Visit(DivExpression* expression) {
  last_value_set_ = VisitAndSetValue(expression->first_) /
                    VisitAndSetValue(expression->second_);
}

void FunctionCallVisitor::Visit(SubstractExpression* expression) {
  last_value_set_ = VisitAndSetValue(expression->first_) -
                    VisitAndSetValue(expression->second_);
}

void FunctionCallVisitor::Visit(IdentExpression* expression) {
  last_value_set_ = GetValue(Symbol(expression->name_));
}

void FunctionCallVisitor::Visit(NumExpression* expression) {
  last_value_set_ = expression->value_;
}

void FunctionCallVisitor::Visit(Program* program) {
}

void FunctionCallVisitor::Visit(PrintStatement* print) {
  std::cout << VisitAndSetValue(print->expr_) << std::endl;
}

void FunctionCallVisitor::Visit(ReadStatement* read) {
  std::cin >> last_value_set_;
  SetValue(Symbol(read->GetVariableName()), last_value_set_);
}

void FunctionCallVisitor::Visit(EqualExpression* eq) {
  last_value_set_ =
      (VisitAndSetValue(eq->first_) == VisitAndSetValue(eq->second_));
}

void FunctionCallVisitor::Visit(LessExpression* less) {
  last_value_set_ =
      (VisitAndSetValue(less->first_) < VisitAndSetValue(less->second_));
}

void FunctionCallVisitor::Visit(GreaterExpression* expr) {
  last_value_set_ =
      (VisitAndSetValue(expr->first_) > VisitAndSetValue(expr->second_));
}

void FunctionCallVisitor::Visit(LessOrEqualExpression* expr) {
  last_value_set_ =
      (VisitAndSetValue(expr->first_) <= VisitAndSetValue(expr->second_));
}

void FunctionCallVisitor::Visit(GreaterOrEqualExpression* expr) {
  last_value_set_ =
      (VisitAndSetValue(expr->first_) >= VisitAndSetValue(expr->first_));
}

void FunctionCallVisitor::Visit(IfStatement* if_statement) {
  if (VisitAndSetValue(if_statement->ifExpression_)) {
    if_statement->then_->AcceptVisitor(this);
    if (if_statement->else_ != nullptr) {
      current_children_.back()++;
    }
  } else {
    current_children_.back()++;
    if (if_statement->else_ != nullptr) {
      if_statement->else_->AcceptVisitor(this);
    }
  }
}

void FunctionCallVisitor::Visit(Scope* scope) {
  current_layer_ = current_layer_->GetChildren(current_children_.back());
  current_children_.push_back(0);
  frame_.BeginScope();
  table_.BeginScope();

  scope->statements_->AcceptVisitor(this);

  frame_.EndScope();
  table_.EndScope();

  current_children_.pop_back();
  current_children_.back()++;

  current_layer_ = current_layer_->GetParent();
}

void FunctionCallVisitor::Visit(VariableDeclaration* decl) {
  table_.DeclareVariable(Symbol(decl->name_), frame_.AllocVariable());
}

void FunctionCallVisitor::Visit(ModuloExpression* expression) {
  last_value_set_ = VisitAndSetValue(expression->first_) %
                    VisitAndSetValue(expression->second_);
}

void FunctionCallVisitor::Visit(WhileStatement* statement) {
  while (VisitAndSetValue(statement->check_expression_)) {
    Visit(statement->scope_);
    if (returned_) {
      return;
    }
    current_children_.back()--;
  }
}

void FunctionCallVisitor::Visit(CallArgumentList* list) {
}

void FunctionCallVisitor::Visit(Function* function) {
  function->arguments_->AcceptVisitor(this);
  function->statements_->AcceptVisitor(this);
}

int FunctionCallVisitor::GetValue(const Symbol& symbol) {
  return frame_.GetValue(table_.GetIndex(symbol));
}

void FunctionCallVisitor::SetValue(const Symbol& symb, int value) {
  frame_.SetValue(table_.GetIndex(symb), value);
}

void FunctionCallVisitor::Visit(FuncArgumentList* list) {
  int index = -1;
  for (auto argument : list->names_) {
    table_.DeclareVariable(Symbol(argument), index);
    --index;
  }
}

void FunctionCallVisitor::Visit(FunctionList*) {
}

FunctionCallVisitor::FunctionCallVisitor(Frame frame, FunctionMap& functions,
                                         ScopeLayerTree& tree,
                                         ScopeLayer* layer)
    : frame_(std::move(frame)),
      functions_(functions),
      tree_(tree),
      current_children_({0}),
      current_layer_(layer) {
}

void FunctionCallVisitor::ExecuteCode(Function* func) {
  Visit(func);
}

void FunctionCallVisitor::Visit(FuncCallExpression* expression) {
  std::vector<int> args;
  for (auto expr : expression->arguments_->arguments_) {
    args.push_back(VisitAndSetValue(expr));
  }
  Frame frame(args);
  frame.SetParent(&frame_);

  auto call_function = functions_.Get(Symbol(expression->name_));
  FunctionCallVisitor visitor(std::move(frame), functions_, tree_,
                              tree_.Get(Symbol(expression->name_)));
  visitor.ExecuteCode(call_function);
  last_value_set_ = frame_.GetReturnValue();
}

void FunctionCallVisitor::Visit(ReturnStatement* statement) {
  VisitAndSetValue(statement->expression_);
  if (frame_.HasParent()) {
    frame_.SetParentReturnValue(last_value_set_);
  }
  returned_ = true;
}

void FunctionCallVisitor::Visit(FuncCallStatement* statement) {
  statement->expression_->AcceptVisitor(this);
}


#include "TypeChecker.h"
#include <include/sources.h>
#include "include/error_macro.h"

void TypeChecker::Visit(StatementList* statements) {
  for (auto statement : statements->statements_) {
    statement->AcceptVisitor(this);
  }
}

void TypeChecker::Visit(Assignment* assignment) {
  auto type = current_layer_->GetValue(Symbol(assignment->variable_));
  if (type->IsFunction()) {
    ERROR("Can't assign to a function");
  }

  assignment->expression_->AcceptVisitor(this);
  if (assignment->expression_->Type()->IsFunction()) {
    ERROR("Function can't be assigned");
  }
  if (type->IsUserClass() && assignment->expression_->Type()->IsUserClass()) {
    auto type1 = dynamic_cast<UserClassType*>(type.get());
    auto type2 = (UserClassType*)assignment->expression_->Type();
    if (type1->name_ != type2->name_) {
      ERROR("No viable conversion from " + type2->name_ + " to " +
            type1->name_);
    }
  }
}

bool CheckIntegerOperation(BinaryExpression* expression) {
  auto a1 = expression->first_->Type()->IsInteger();
  auto a2 = expression->first_->Type()->IsBool();
  auto a3 = expression->first_->Type()->IsInteger();
  auto a4 = expression->first_->Type()->IsBool();
  return !(a1 || a2) || !(a3 || a4);
}

void TypeChecker::Visit(AddExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
  if (CheckIntegerOperation(expression)) {
    ERROR("No matching operation");
  }
  expression->Type() = new Integer(0);
}
void TypeChecker::Visit(MulExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
  if (CheckIntegerOperation(expression)) {
    ERROR("No matching operation");
  }
  expression->Type() = new Integer(0);
}

void TypeChecker::Visit(DivExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
  if (CheckIntegerOperation(expression)) {
    ERROR("No matching operation");
  }
  expression->Type() = new Integer(0);
}

void TypeChecker::Visit(SubstractExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
  if (CheckIntegerOperation(expression)) {
    ERROR("No matching operation");
  }
  expression->Type() = new Integer(0);
}

void TypeChecker::Visit(IdentExpression* expression) {
  expression->Type() =
      current_layer_->GetValue(Symbol(expression->name_)).get();
}

void TypeChecker::Visit(NumExpression* expression) {
  expression->Type() = new Integer(0);
}

void TypeChecker::Visit(Program* program) {
  program->AcceptVisitor(this);
}

void TypeChecker::Visit(PrintStatement* print) {
  print->expr_->AcceptVisitor(this);
  auto type = print->expr_->Type();
  if (!type->IsBool() && !type->IsInteger()) {
    ERROR("Can print only Integer and Bool");
  }
}

void TypeChecker::Visit(ReadStatement*) {
}

void TypeChecker::Visit(EqualExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
  if (CheckIntegerOperation(expression)) {
    ERROR("No matching operation");
  }
  expression->Type() = new BoolType(false);
}

void TypeChecker::Visit(LessExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
  if (CheckIntegerOperation(expression)) {
    ERROR("No matching operation");
  }
  expression->Type() = new BoolType(false);
}

void TypeChecker::Visit(GreaterExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
  if (CheckIntegerOperation(expression)) {
    ERROR("No matching operation");
  }
  expression->Type() = new BoolType(false);
}

void TypeChecker::Visit(LessOrEqualExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
  if (CheckIntegerOperation(expression)) {
    ERROR("No matching operation");
  }
  expression->Type() = new BoolType(false);
}

void TypeChecker::Visit(GreaterOrEqualExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
  if (CheckIntegerOperation(expression)) {
    ERROR("No matching operation");
  }
  expression->Type() = new BoolType(false);
}

void TypeChecker::Visit(IfStatement* if_statement) {
  if_statement->then_->AcceptVisitor(this);
  if (if_statement->else_ != nullptr) {
    if_statement->else_->AcceptVisitor(this);
  }
  if_statement->ifExpression_->AcceptVisitor(this);
  auto type = if_statement->ifExpression_->Type();
  if (!type->IsBool() && !type->IsInteger()) {
    ERROR("If statement must have bool or integer type");
  }
}

void TypeChecker::Visit(Scope* scope) {
  current_layer_ = current_layer_->GetChildren(current_children_.back()++);
  current_children_.push_back(0);

  scope->statements_->AcceptVisitor(this);

  current_children_.pop_back();
  current_layer_ = current_layer_->GetParent();
}

void TypeChecker::Visit(VariableDeclaration* vardecl) {
}

TypeChecker::TypeChecker(ScopeLayer* root, FunctionMap& map)
    : current_layer_(root), current_children_({0}), func_map_(map) {
}

void TypeChecker::Visit(ModuloExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
  if (CheckIntegerOperation(expression)) {
    ERROR("No matching operation");
  }
  expression->Type() = new Integer(0);
}

void TypeChecker::Visit(WhileStatement* while_statement) {
  while_statement->scope_->AcceptVisitor(this);
  while_statement->check_expression_->AcceptVisitor(this);
  auto type = while_statement->check_expression_->Type();
  if (!type->IsBool() && !type->IsInteger()) {
    ERROR("If statement must have bool or integer type");
  }
}

void TypeChecker::CheckType(Program* program) {
  Visit(program);
}

void TypeChecker::Visit(Function* function) {
  current_layer_ = current_layer_->GetChildren(current_children_.back()++);
  current_children_.push_back(0);
  function->statements_->AcceptVisitor(this);
  current_children_.pop_back();
  current_layer_ = current_layer_->GetParent();
}

void TypeChecker::Visit(FunctionList* list) {
  for (auto function : list->functions_) {
    function->AcceptVisitor(this);
  }
}

void TypeChecker::Visit(FuncArgumentList*) {
}

void TypeChecker::Visit(CallArgumentList*) {
}

void TypeChecker::Visit(FuncCallExpression* expression) {
  auto type = current_layer_->GetValue(Symbol(expression->name_));
  if (!type->IsFunction()) {
    ERROR(expression->name_ + "is not a function\n");
  }
  expression->Type() =
      func_map_.Get(Symbol(expression->name_))->return_type_->GetType();
}

void TypeChecker::Visit(ReturnStatement* statement) {
}

void TypeChecker::Visit(FuncCallStatement* statement) {
  statement->expression_->AcceptVisitor(this);
}

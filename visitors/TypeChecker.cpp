
#include "TypeChecker.h"
#include <include/sources.h>
#include "include/macros.h"
#include "types/TypesSupport.cpp"

void TypeChecker::Visit(StatementList* statements) {
  for (auto statement : statements->statements_) {
    statement->AcceptVisitor(this);
  }
}

void TypeChecker::Visit(Assignment* assignment) {
  auto left_type = current_layer_->GetType(Symbol(assignment->variable_));
  if (left_type->IsFunction()) {
    ERROR("Can't assign to a function", assignment);
  }
  auto right_type = VisitAndReturnValue(assignment->expression_);
  if (!IsConvertible(left_type, right_type)) {
    ERROR("Can not assign " + right_type->TypeName() + " to " +
              left_type->TypeName(),
          assignment);
  }
}

void TypeChecker::CheckIntegerOperation(BinaryExpression* expression) {
  auto first_type = VisitAndReturnValue(expression->second_);
  auto second_type = VisitAndReturnValue(expression->first_);

  bool result = IsConvertible(first_type, second_type);
  if (!result) {
    ERROR("Invalid operands to binary expression (\"" + first_type->TypeName() +
              "\" and \"" + second_type->TypeName() + "\")",
          expression);
  }
}

void TypeChecker::Visit(AddExpression* expression) {
  CheckIntegerOperation(expression);
  last_value_set_ = std::make_shared<IntegerType>();
}

void TypeChecker::Visit(MulExpression* expression) {
  CheckIntegerOperation(expression);
  last_value_set_ = std::make_shared<IntegerType>();
}

void TypeChecker::Visit(DivExpression* expression) {
  CheckIntegerOperation(expression);
  last_value_set_ = std::make_shared<IntegerType>();
}

void TypeChecker::Visit(SubstractExpression* expression) {
  CheckIntegerOperation(expression);
  last_value_set_ = std::make_shared<IntegerType>();
}

void TypeChecker::Visit(IdentExpression* expression) {
  last_value_set_ = current_layer_->GetType(Symbol(expression->name_));
}

void TypeChecker::Visit(NumExpression* expression) {
  last_value_set_ = std::make_shared<IntegerType>();
}

void TypeChecker::Visit(Program* program) {
  program->AcceptVisitor(this);
}

void TypeChecker::Visit(PrintStatement* print) {
  auto type = VisitAndReturnValue(print->expr_);
  if (!type->IsBool() && !type->IsInteger()) {
    ERROR("Can print only Integer and Bool", print);
  }
}

void TypeChecker::Visit(ReadStatement* read) {
  auto type = current_layer_->GetType(Symbol(read->GetVariableName()));
  if (!type->IsBool() && !type->IsInteger()) {
    ERROR("Can not read variable of type \"" + type->TypeName() + "\"", read);
  }
}

void TypeChecker::Visit(EqualExpression* expression) {
  CheckIntegerOperation(expression);
  last_value_set_ = std::make_shared<BoolType>();
}

void TypeChecker::Visit(LessExpression* expression) {
  CheckIntegerOperation(expression);
  last_value_set_ = std::make_shared<BoolType>();
}

void TypeChecker::Visit(GreaterExpression* expression) {
  CheckIntegerOperation(expression);
  last_value_set_ = std::make_shared<BoolType>();
}

void TypeChecker::Visit(LessOrEqualExpression* expression) {
  CheckIntegerOperation(expression);
  last_value_set_ = std::make_shared<BoolType>();
}

void TypeChecker::Visit(GreaterOrEqualExpression* expression) {
  CheckIntegerOperation(expression);
  last_value_set_ = std::make_shared<BoolType>();
}

void TypeChecker::Visit(IfStatement* if_statement) {
  if_statement->then_->AcceptVisitor(this);
  if (if_statement->else_ != nullptr) {
    if_statement->else_->AcceptVisitor(this);
  }
  auto type = VisitAndReturnValue(if_statement->ifExpression_);
  if (!type->IsBool() && !type->IsInteger()) {
    ERROR("If expression must have bool or integer type", if_statement);
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
  auto right_type = VisitAndReturnValue(vardecl->expression_);
  auto left_type = CreateTypePtr(vardecl->type_name_);
  if (!left_type->IsSameWith(right_type) &&
      !IsConvertible(right_type, left_type)) {
    ERROR("Can not assign " + right_type->TypeName() + " to " +
              left_type->TypeName(),
          vardecl);
  }
}

TypeChecker::TypeChecker(ScopeLayer* root, FunctionMap& map,
                         ScopeLayerTree& tree)
    : current_layer_(root),
      current_children_({0}),
      func_map_(map),
      tree_(tree) {
}

void TypeChecker::Visit(ModuloExpression* expression) {
  CheckIntegerOperation(expression);
  last_value_set_ = std::make_shared<IntegerType>();
}

void TypeChecker::Visit(WhileStatement* while_statement) {
  while_statement->scope_->AcceptVisitor(this);
  auto type = VisitAndReturnValue(while_statement->check_expression_);
  if (!type->IsBool() && !type->IsInteger()) {
    ERROR("While expression must have bool or integer type", while_statement);
  }
}

void TypeChecker::CheckType(Program* program) {
  Visit(program->classes_);
  Visit(program->main_);
}

void TypeChecker::Visit(ClassMethod* function) {
  current_layer_ = current_layer_->GetChildren(current_children_.back()++);
  current_children_.push_back(0);

  function->statements_->AcceptVisitor(this);

  current_children_.pop_back();
  current_layer_ = current_layer_->GetParent();
}

void TypeChecker::Visit(ClassBody* list) {
  for (auto function : list->methods_) {
    current_method_ = function;
    function->AcceptVisitor(this);
  }
}

void TypeChecker::Visit(MethodArgumentList*) {
}

void TypeChecker::Visit(CallArgumentList* list) {
}

void TypeChecker::Visit(MethodCallExpression* expression) {
  auto expr_type = VisitAndReturnValue(expression->expression_);

  if (!expr_type->IsClass()) {
    ERROR("Can not call method from non-class object", expression);
  }

  ScopeLayer* class_scope = tree_.Get(Symbol(expr_type->TypeName()));
  expression->class_type_name_ = expr_type->TypeName();
  if (!class_scope->HasSymbol(Symbol(expression->name_))) {
    ERROR("Class \"" + expr_type->TypeName() + "\" has no member \"" +
              expression->name_ + "\"",
          expression)
  }
  auto type = class_scope->GetType(Symbol(expression->name_));

  if (!type->IsFunction()) {
    ERROR(expression->name_ + "is not a function\n", expression);
  }

  ClassMethod* callee_method =
      func_map_.Get(Symbol(expr_type->TypeName() + "::" + expression->name_));

  size_t callee_arguments = callee_method->arguments_->names_.size();
  size_t passed_arguments = expression->arguments_->arguments_.size();

  if (callee_arguments != passed_arguments) {
    ERROR(std::to_string(callee_arguments) + " Arguments expected, but " +
              std::to_string(passed_arguments) + " were given\n",
          expression);
  }

  for (size_t i = 0; i < callee_arguments; ++i) {
    auto arg_type = VisitAndReturnValue(expression->arguments_->arguments_[i]);
    auto func_type = CreateTypePtr(callee_method->arguments_->types_[i]);
    if (!IsConvertible(arg_type, func_type) &&
        !arg_type->IsSameWith(func_type)) {
      ERROR("Expected \"" + func_type->TypeName() + "\" but " +
                arg_type->TypeName() + "\" was given",
            expression);
    }
  }

  std::shared_ptr<FunctionType> method_type =
      std::dynamic_pointer_cast<FunctionType>(type);
  last_value_set_ = method_type->GetReturnType();
}

void TypeChecker::Visit(ReturnStatement* statement) {
  if (statement->expression_ == nullptr &&
      current_method_->return_type_ != "void") {
    ERROR("Expected return expression", statement);
  }
  if (statement->expression_ != nullptr &&
      current_method_->return_type_ == "void") {
    ERROR("Expected no return expression", statement);
  }
  if (statement->expression_ == nullptr) {
    return;
  }
  auto type = VisitAndReturnValue(statement->expression_);
  auto return_type = CreateTypePtr(current_method_->return_type_);
  if (!IsConvertible(type, return_type) && !type->IsSameWith(return_type)) {
    ERROR("Return type is \"" + return_type->TypeName() + "\" but \"" +
              type->TypeName() + "\" was given",
          statement);
  }
}

void TypeChecker::Visit(MethodCallStmt* statement) {
  statement->expression_->AcceptVisitor(this);
}

void TypeChecker::Visit(Class* cl) {
  current_layer_ = current_layer_->GetChildren(current_children_.back()++);

  current_children_.push_back(0);
  cl->body_->AcceptVisitor(this);

  current_children_.pop_back();
  current_layer_ = current_layer_->GetParent();
}

void TypeChecker::Visit(ClassList* list) {
  for (auto cl : list->classes_) {
    current_class_ = cl;
    cl->AcceptVisitor(this);
  }
}

void TypeChecker::Visit(ClassField*) {
}

void TypeChecker::Visit(ClassMain* main) {
  main->main_->AcceptVisitor(this);
}

void TypeChecker::Visit(ThisExpression*) {
  last_value_set_ = std::make_shared<ClassType>(current_class_->name_);
}

void TypeChecker::Visit(NewExpression* expression) {
  last_value_set_ = CreateTypePtr(expression->type_);
}

void TypeChecker::Visit(ArrayDeclaration*) {
}

void TypeChecker::Visit(ArrayAssignment* assignment) {
  auto array_type = std::dynamic_pointer_cast<ArrayType>(
      current_layer_->GetType(Symbol(assignment->array_name_)));

  if (array_type == nullptr) {
    ERROR("\"" + assignment->array_name_ + "\" is not an array!", assignment);
  }
  auto left_type = array_type->array_type_;
  auto right_type = VisitAndReturnValue(assignment->expression_);
  if (!IsConvertible(left_type, right_type)) {
    ERROR("Cannot assign \"" + right_type->TypeName() + "\" to \"" +
              left_type->TypeName(),
          assignment);
  }
}

void TypeChecker::Visit(ArrayExpression* expression) {
  auto array_type = std::dynamic_pointer_cast<ArrayType>(
      current_layer_->GetType(Symbol(expression->name_)));

  if (array_type == nullptr) {
    ERROR("\"" + expression->name_ + "\" is not an array!", expression);
  }
  last_value_set_ = array_type->array_type_;
}

void TypeChecker::Visit(LogicOrExpression* expression) {
  auto left_type = VisitAndReturnValue(expression->first_);
  auto right_type = VisitAndReturnValue(expression->second_);
  if (!left_type->IsBool() && !left_type->IsInteger()) {
    ERROR("Cannot convert + \"" + left_type->TypeName() + "\" to Bool",
          expression);
  }
  if (!right_type->IsBool() && !right_type->IsInteger()) {
    ERROR("Cannot convert + \"" + right_type->TypeName() + "\" to Bool",
          expression);
  }
  last_value_set_ = CreateTypePtr("Bool");
}

void TypeChecker::Visit(LogicAndExpression* expression) {
  auto left_type = VisitAndReturnValue(expression->first_);
  auto right_type = VisitAndReturnValue(expression->second_);
  if (!left_type->IsBool() && !left_type->IsInteger()) {
    ERROR("Cannot convert + \"" + left_type->TypeName() + "\" to Bool",
          expression);
  }
  if (!right_type->IsBool() && !right_type->IsInteger()) {
    ERROR("Cannot convert + \"" + right_type->TypeName() + "\" to Bool",
          expression);
  }
  last_value_set_ = CreateTypePtr("Bool");
}

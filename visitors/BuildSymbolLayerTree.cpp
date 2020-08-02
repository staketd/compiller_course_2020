
#include "BuildSymbolLayerTree.h"
#include <include/sources.h>
#include "include/macros.h"
#include "types/TypesSupport.cpp"

void BuildSymbolLayerTree::Visit(StatementList* statements) {
  for (auto statement : statements->statements_) {
    statement->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(Assignment* assignment) {
  assignment->expression_->AcceptVisitor(this);
  if (!current_layer_->WasDeclared(Symbol(assignment->variable_))) {
    ERROR("Variable \"" + assignment->variable_ + "\" was not declared",
          assignment);
  }
}

void BuildSymbolLayerTree::Visit(AddExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(MulExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(DivExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(SubstractExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(IdentExpression* expression) {
  if (!current_layer_->WasDeclared(Symbol(expression->name_))) {
    ERROR("Variable \"" + expression->name_ + "\" was not declared",
          expression);
  }
}

void BuildSymbolLayerTree::Visit(NumExpression*) {
}

void BuildSymbolLayerTree::Visit(Program* program) {
  Visit(program->classes_);
  Visit(program->main_);
}

void BuildSymbolLayerTree::Visit(PrintStatement* statement) {
  statement->expr_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(ReadStatement* statement) {
  if (!current_layer_->WasDeclared(Symbol(statement->GetVariableName()))) {
    ERROR("Variable \"" + statement->GetVariableName() + "\" was not declared",
          statement);
  }
}

void BuildSymbolLayerTree::Visit(EqualExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(LessExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(GreaterExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(LessOrEqualExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(GreaterOrEqualExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(IfStatement* if_statement) {
  if_statement->ifExpression_->AcceptVisitor(this);
  if_statement->then_->AcceptVisitor(this);
  if (if_statement->else_ != nullptr) {
    if_statement->else_->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(Scope* scope) {
  current_layer_ = current_layer_->CreateChildren();
  scope->statements_->AcceptVisitor(this);
  current_layer_ = current_layer_->GetParent();
}

void BuildSymbolLayerTree::Visit(VariableDeclaration* vardecl) {
  vardecl->expression_->AcceptVisitor(this);
  if (!IsCorrectVariableType(vardecl->type_name_)) {
    ERROR("Incorrect variable type + \"" + vardecl->type_name_ + "\"", vardecl);
  }
  current_layer_->DeclareSymbol(Symbol(vardecl->name_),
                                CreateTypePtr(vardecl->type_name_));
}

void BuildSymbolLayerTree::Visit(ModuloExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(WhileStatement* while_statement) {
  while_statement->scope_->AcceptVisitor(this);
  while_statement->check_expression_->AcceptVisitor(this);
}

BuildSymbolLayerTree::BuildSymbolLayerTree(ScopeLayerTree& root,
                                           FunctionMap& map, ClassMap& c_map)
    : tree_(root),
      current_layer_(root.GetRoot()),
      functions_(map),
      class_map_(c_map) {
}

void BuildSymbolLayerTree::BuildTree(Program* program) {
  Visit(program);
}

void BuildSymbolLayerTree::Visit(CallArgumentList* call) {
  for (auto expr : call->arguments_) {
    expr->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(ClassMethod* function) {
  if (!IsCorrectVariableType(function->return_type_) &&
      function->return_type_ != "void") {
    ERROR("Incorrect return type \"" + function->return_type_ + "\"", function);
  }
  current_layer_->DeclareSymbol(
      Symbol(function->name_),
      std::make_shared<FunctionType>(CreateTypePtr(function->return_type_)));
  current_layer_ = current_layer_->CreateChildren();

  functions_.Set(Symbol(current_class_name_ + "::" + function->name_),
                 function);

  function->arguments_->AcceptVisitor(this);
  function->statements_->AcceptVisitor(this);

  tree_.AddMapping(Symbol(current_class_name_ + "::" + function->name_),
                   current_layer_);

  current_layer_ = current_layer_->GetParent();
}

void BuildSymbolLayerTree::Visit(MethodArgumentList* list) {
  for (size_t i = 0; i < list->types_.size(); ++i) {
    auto& name = list->names_[i];
    auto& type = list->types_[i];
    if (!IsCorrectVariableType(type)) {
      ERROR("Incorrect variable type \"" + type + "\"", list);
    }
    current_layer_->DeclareSymbol(Symbol(name), CreateTypePtr(type));
  }
}

void BuildSymbolLayerTree::Visit(ClassBody* list) {
  for (auto var : list->fields_) {
    current_class_layout_->AddField(Symbol(var->name_));
    var->AcceptVisitor(this);
  }
  for (auto func : list->methods_) {
    func->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(MethodCallExpression* expression) {
  expression->expression_->AcceptVisitor(this);

  for (auto expr : expression->arguments_->arguments_) {
    expr->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(ReturnStatement* statement) {
  if (statement->expression_ != nullptr) {
    statement->expression_->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(MethodCallStmt* statement) {
  statement->expression_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(Class* cl) {
  class_map_.SetClass(Symbol(cl->name_), cl);
  current_class_layout_ = new ClassLayout(cl->name_);
  class_map_.SetClassLayout(Symbol(cl->name_), current_class_layout_);
  current_layer_->DeclareSymbol(Symbol(cl->name_),
                                std::make_shared<ClassType>(cl->name_));

  current_layer_ = current_layer_->CreateChildren();

  tree_.AddMapping(Symbol(cl->name_), current_layer_);

  cl->body_->AcceptVisitor(this);

  current_layer_ = current_layer_->GetParent();
}

void BuildSymbolLayerTree::Visit(ClassList* list) {
  for (auto elem : list->classes_) {
    current_class_name_ = elem->name_;
    elem->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(ClassField* field) {
  if (!IsCorrectVariableType(field->type_) ||
      field->type_ == current_class_name_) {
    ERROR("Incorrect field type \"" + field->type_ + "\"", field);
  }
  current_layer_->DeclareSymbol(Symbol(field->name_),
                                CreateTypePtr(field->type_));
}

void BuildSymbolLayerTree::Visit(ClassMain* main) {
  current_layer_->DeclareSymbol(Symbol(main->name_),
                                std::make_shared<ClassType>(main->name_));
  tree_.AddMapping(Symbol(main->name_), current_layer_);

  current_class_name_ = main->name_;

  main->main_->AcceptVisitor(this);
}

bool BuildSymbolLayerTree::IsCorrectVariableType(const std::string& type) {
  if (IsPrimitiveType(type)) {
    return true;
  }
  if (current_layer_->WasDeclared(Symbol(type))) {
    return current_layer_->GetType(Symbol(type))->TypeName() == type;
  }
  return false;
}

void BuildSymbolLayerTree::Visit(ThisExpression*) {
}

void BuildSymbolLayerTree::Visit(NewExpression* expression) {
}

void BuildSymbolLayerTree::Visit(ArrayDeclaration* decl) {
  if (!IsCorrectVariableType(decl->array_type_)) {
    ERROR("Incorrect Array Type: \"" + decl->array_type_ + "\"", decl);
  }
  current_layer_->DeclareSymbol(
      Symbol(decl->name_),
      std::make_shared<ArrayType>(CreateTypePtr(decl->array_type_)));
}

void BuildSymbolLayerTree::Visit(ArrayAssignment* assignment) {
  if (!current_layer_->WasDeclared(Symbol(assignment->array_name_))) {
    ERROR("Variable \"" + assignment->array_name_ + "\" was not declared",
          assignment);
  }
  assignment->expression_->AcceptVisitor(this);
  assignment->ind_expression_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(ArrayExpression* expression) {
  if (!current_layer_->WasDeclared(Symbol(expression->name_))) {
    ERROR("Variable \"" + expression->name_ + "\" was not declared",
          expression);
  }
  expression->expression_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(LogicAndExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
}
void BuildSymbolLayerTree::Visit(LogicOrExpression* expression) {
  expression->first_->AcceptVisitor(this);
  expression->second_->AcceptVisitor(this);
}


#include "BuildSymbolLayerTree.h"
#include <include/sources.h>
#include "include/error_macro.h"
#include <BaseType.h>

std::shared_ptr<BaseType> CreateTypePtr(const std::string type_name) {
  if (type_name == "Integer") {
    return std::make_shared<Integer>();
  } else if (type_name == "Bool") {
    return std::make_shared<BoolType>();
  }
  return nullptr;
}

void BuildSymbolLayerTree::Visit(StatementList* statements) {
  for (auto statement : statements->statements_) {
    statement->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(Assignment* assignment) {
  assignment->expression_->AcceptVisitor(this);
  if (!current_layer_->WasDeclared(Symbol(assignment->variable_))) {
    ERROR("Variable \"" + assignment->variable_ + "\" was not declared");
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
    ERROR("Variable \"" + expression->name_ + "\" was not declared");
  }
}

void BuildSymbolLayerTree::Visit(NumExpression*) {
}

void BuildSymbolLayerTree::Visit(Program* program) {
  program->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(PrintStatement* statement) {
  statement->expr_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(ReadStatement* statement) {
  if (!current_layer_->WasDeclared(Symbol(statement->GetVariableName()))) {
    ERROR("Variable \"" + statement->GetVariableName() + "\" was not declared");
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
  current_layer_->DeclareSymbol(Symbol(vardecl->name_),
                                CreateTypePtr(vardecl->type_name_));
}

void BuildSymbolLayerTree::Visit(ModuloExpression*) {
}

void BuildSymbolLayerTree::Visit(WhileStatement* while_statement) {
  while_statement->scope_->AcceptVisitor(this);
}

BuildSymbolLayerTree::BuildSymbolLayerTree(ScopeLayerTree& root,
                                           FunctionMap& map)
    : tree_(root), current_layer_(root.GetRoot()), functions_(map){
}

void BuildSymbolLayerTree::BuildTree(Program* program) {
  Visit(program);
}

void BuildSymbolLayerTree::Visit(CallArgumentList* call) {
  for (auto expr : call->arguments_) {
    expr->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(Function* function) {
  current_layer_->DeclareSymbol(Symbol(function->name_),
                                std::make_shared<FunctionType>());

  functions_.Set(Symbol(function->name_), function);
  current_layer_ = current_layer_->CreateChildren();
  function->arguments_->AcceptVisitor(this);
  function->statements_->AcceptVisitor(this);

  tree_.AddMapping(Symbol(function->name_), current_layer_);

  current_layer_ = current_layer_->GetParent();
}

void BuildSymbolLayerTree::Visit(FuncArgumentList* list) {
  for (auto name : list->names_) {
    current_layer_->DeclareSymbol(Symbol(name), CreateTypePtr("Integer"));
  }
}

void BuildSymbolLayerTree::Visit(FunctionList* list) {
  for (auto func: list->functions_) {
    func->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(FuncCallExpression* expression) {
  for (auto expr: expression->arguments_->arguments_) {
    expr->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(ReturnStatement* statement) {
  statement->expression_->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(FuncCallStatement* statement) {
  statement->expression_->AcceptVisitor(this);
}

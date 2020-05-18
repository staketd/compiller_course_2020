
#include "BuildSymbolLayerTree.h"
#include <include/sources.h>
#include "include/error_macro.h"

void BuildSymbolLayerTree::Visit(StatementList* statements) {
  for (auto statement : statements->statements_) {
    statement->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(Assignment* assignment) {
  if (!current_layer_->WasDeclared(Symbol(assignment->variable_))) {
    ERROR("Variable \"" + assignment->variable_ + "\" was not declared");
  }
}

void BuildSymbolLayerTree::Visit(AddExpression*) {
}

void BuildSymbolLayerTree::Visit(MulExpression*) {
}

void BuildSymbolLayerTree::Visit(DivExpression*) {
}

void BuildSymbolLayerTree::Visit(SubstractExpression*) {
}

void BuildSymbolLayerTree::Visit(IdentExpression* expression) {
  if (!current_layer_->WasDeclared(Symbol(expression->ident_))) {
    ERROR("Variable \"" + expression->ident_ + "\" was not declared");
  }
}

void BuildSymbolLayerTree::Visit(NumExpression*) {
}

void BuildSymbolLayerTree::Visit(Program* program) {
  program->AcceptVisitor(this);
}

void BuildSymbolLayerTree::Visit(PrintStatement*) {
}

void BuildSymbolLayerTree::Visit(ReadStatement*) {
}

void BuildSymbolLayerTree::Visit(EqualExpression*) {
}

void BuildSymbolLayerTree::Visit(LessExpression*) {
}

void BuildSymbolLayerTree::Visit(GreaterExpression*) {
}

void BuildSymbolLayerTree::Visit(LessOrEqualExpression*) {
}

void BuildSymbolLayerTree::Visit(GreaterOrEqualExpression*) {
}

void BuildSymbolLayerTree::Visit(IfStatement* if_statement) {
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
  current_layer_->DeclareVariable(Symbol(vardecl->name_));
}

void BuildSymbolLayerTree::Visit(ModuloExpression*) {
}

void BuildSymbolLayerTree::Visit(WhileStatement* while_statement) {
  while_statement->scope_->AcceptVisitor(this);
}

BuildSymbolLayerTree::BuildSymbolLayerTree(ScopeLayer* root)
    : current_layer_(root) {
}

void BuildSymbolLayerTree::BuildTree(Program* program) {
  Visit(program);
}

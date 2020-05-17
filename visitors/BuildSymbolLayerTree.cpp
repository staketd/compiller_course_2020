
#include "BuildSymbolLayerTree.h"
#include <sources.h>

void BuildSymbolLayerTree::Visit(StatementList* statements) {
  for (auto statement : statements->statements_) {
    statement->AcceptVisitor(this);
  }
}

void BuildSymbolLayerTree::Visit(Assignment*) {
}

void BuildSymbolLayerTree::Visit(AddExpression*) {
}

void BuildSymbolLayerTree::Visit(MulExpression*) {
}

void BuildSymbolLayerTree::Visit(DivExpression*) {
}

void BuildSymbolLayerTree::Visit(SubstractExpression*) {
}

void BuildSymbolLayerTree::Visit(IdentExpression*) {
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

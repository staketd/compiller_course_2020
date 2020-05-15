
#include <iostream>
#include "Interprenter.h"

#include "sources.h"
#include <Integer.h>

void Interprenter::Visit(StatementList* statements) {
    for (auto statement: statements->statements_) {
        statement->AcceptVisitor(this);
    }
}

void Interprenter::Visit(Assignment* assignment) {
    auto value = std::make_shared<Integer>(VisitAndSetValue(assignment->expression_));
    symbol_table_.SetValue(Symbol(assignment->variable_), value);
}

void Interprenter::Visit(AddExpression* addExpression) {
    last_value_set_ = VisitAndSetValue(addExpression->first_) + VisitAndSetValue(addExpression->second_);
}

void Interprenter::Visit(MulExpression* expression) {
    last_value_set_ = VisitAndSetValue(expression->first_) * VisitAndSetValue(expression->second_);
}

void Interprenter::Visit(DivExpression* expression) {
    last_value_set_ = VisitAndSetValue(expression->first_) / VisitAndSetValue(expression->second_);
}

void Interprenter::Visit(SubstractExpression* expression) {
    last_value_set_= VisitAndSetValue(expression->first_) - VisitAndSetValue(expression->second_);
}

void Interprenter::Visit(IdentExpression* expression) {
    last_value_set_ = symbol_table_.GetValue(Symbol(expression->ident_))->ToInt();
}

void Interprenter::Visit(NumExpression* expression) {
    last_value_set_ = expression->value_;
}

void Interprenter::Visit(Program* program) {
    program->AcceptVisitor(this);
}

void Interprenter::ExecuteCode(Program* program) {
    program->AcceptVisitor(this);
}

Interprenter::Interprenter() {
    last_value_set_ = 0;
}

void Interprenter::Visit(PrintStatement* print) {
    std::cout << VisitAndSetValue(print->expr_) << std::endl;
}

void Interprenter::Visit(ReadStatement* read) {
    std::cin >> last_value_set_;
    auto value = std::make_shared<Integer>(last_value_set_);
    symbol_table_.SetValue(Symbol(read->GetVariableName()), value);
}

void Interprenter::Visit(EqualExpression* eq) {
    last_value_set_ = (VisitAndSetValue(eq->first_) == VisitAndSetValue(eq->second_));
}

void Interprenter::Visit(LessExpression* less) {
    last_value_set_ = (VisitAndSetValue(less->first_) < VisitAndSetValue(less->second_));
}

void Interprenter::Visit(GreaterExpression* expr) {
    last_value_set_ = (VisitAndSetValue(expr->first_) > VisitAndSetValue(expr->second_));
}

void Interprenter::Visit(LessOrEqualExpression* expr) {
    last_value_set_ = (VisitAndSetValue(expr->first_) <= VisitAndSetValue(expr->second_));
}

void Interprenter::Visit(GreaterOrEqualExpression* expr) {
    last_value_set_ = (VisitAndSetValue(expr->first_) >= VisitAndSetValue(expr->first_));
}

void Interprenter::Visit(IfStatement* ifStatement) {
    if (VisitAndSetValue(ifStatement->ifExpression_)) {
        ifStatement->then_->AcceptVisitor(this);
    } else if (ifStatement->else_ != nullptr) {
        ifStatement->else_->AcceptVisitor(this);
    }
}

void Interprenter::Visit(Scope* scope) {
    symbol_table_.BeginScope();
    scope->statements_->AcceptVisitor(this);
    symbol_table_.EndScope();
}

void Interprenter::Visit(DeclareStatement* decl) {
    symbol_table_.DeclareVariable(Symbol(decl->name_));
}






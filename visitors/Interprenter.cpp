
#include <iostream>
#include "Interprenter.h"

#include "sources.h"

void Interprenter::Visit(StatementList* statements) {
    for (auto statement: statements->statements_) {
        statement->AcceptVisitor(this);
    }
}

void Interprenter::Visit(Assignment* assignment) {
    variables_[assignment->variable_] = VisitAndSetValue(assignment->expression_);
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
    last_value_set_ = variables_[expression->ident_];
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
    variables_["one"] = 1;
    variables_["two"] = 2;
    last_value_set_ = 0;
}

void Interprenter::Visit(PrintStatement* print) {
    std::cout << VisitAndSetValue(print->expr_) << std::endl;
}

void Interprenter::Visit(ReadStatement* read) {
    std::cin >> last_value_set_;
    variables_[read->GetVariableName()] = last_value_set_;
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
        ifStatement->statements_->AcceptVisitor(this);
    }
}






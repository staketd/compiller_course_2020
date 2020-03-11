
#include <AssignmentList.h>
#include "Interprenter.h"

#include "sources.h"

void Interprenter::Visit(AssignmentList* assignments) {
    for (auto assignment: assignments->assignments_) {
        Visit(assignment);
    }
}

void Interprenter::Visit(Assignment* assignment) {
    assignment->expression_->AcceptVisitor(this);
    variables_[assignment->variable_] = last_calculated_value_;
    UnsetLastValue();
}

void Interprenter::Visit(AddExpression* addExpression) {
    addExpression->first_->AcceptVisitor(this);
    int val = last_calculated_value_;
    addExpression->second_->AcceptVisitor(this);
    val += last_calculated_value_;
    SetLastValue(val);
}

void Interprenter::Visit(MulExpression* expression) {
    expression->first_->AcceptVisitor(this);
    int val = last_calculated_value_;
    expression->second_->AcceptVisitor(this);
    val *= last_calculated_value_;
    SetLastValue(val);
}

void Interprenter::SetLastValue(int value) {
    last_calculated_value_ = value;
    last_value_is_set_ = true;
}

void Interprenter::UnsetLastValue() {
    last_calculated_value_ = 0;
    last_value_is_set_ = false;
}

void Interprenter::Visit(DivExpression* expression) {
    expression->first_->AcceptVisitor(this);
    int val = last_calculated_value_;
    expression->second_->AcceptVisitor(this);
    val /= last_calculated_value_;
    SetLastValue(val);
}

void Interprenter::Visit(SubstractExpression* expression) {
    expression->first_->AcceptVisitor(this);
    int val = last_calculated_value_;
    expression->second_->AcceptVisitor(this);
    val -= last_calculated_value_;
    SetLastValue(val);
}

void Interprenter::Visit(IdentExpression* expression) {
    int value = variables_[expression->ident_];
    SetLastValue(value);
}

void Interprenter::Visit(NumExpression* expression) {
    SetLastValue(expression->value_);
}

void Interprenter::Visit(Program* program) {
    program->assignments_->AcceptVisitor(this);
    program->expression_->AcceptVisitor(this);
}

int Interprenter::ExecuteCode(Program* program) {
    UnsetLastValue();
    Visit(program);
    return last_calculated_value_;
}

Interprenter::Interprenter() {
    variables_["one"] = 1;
    variables_["two"] = 2;
    last_calculated_value_ = 0;
    last_value_is_set_ = false;
}





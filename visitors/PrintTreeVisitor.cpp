
#include <StatementList.h>
#include <AddExpression.h>
#include "PrintTreeVisitor.h"
#include "include/sources.h"

void PrintTreeVisitor::Visit(StatementList* assignmentList) {
    PrintTabs();
    stream_<< "Assignment list: \n";
    ++tabs_num_;
    for (auto statement: assignmentList->statements_) {
        statement->AcceptVisitor(this);
    }
    --tabs_num_;
}

void PrintTreeVisitor::Visit(Assignment* assignment) {
    PrintTabs();
    stream_ << "Assignment of: " << assignment->variable_ << "\n";
    ++tabs_num_;
    assignment->expression_->AcceptVisitor(this);
    --tabs_num_;
}

void PrintTreeVisitor::PrintTabs() {
    for (size_t i = 0; i < tabs_num_; ++i) {
        stream_ << '\t';
    }
}

PrintTreeVisitor::PrintTreeVisitor(const std::string& filename): stream_(filename){
    tabs_num_ = 0;
}

void PrintTreeVisitor::Visit(AddExpression* expression) {
    PrintTabs();
    stream_ << "AddExpression: \n";
    ++tabs_num_;
    expression->first_->AcceptVisitor(this);
    expression->second_->AcceptVisitor(this);
    --tabs_num_;
}

void PrintTreeVisitor::Visit(MulExpression* expression) {
    PrintTabs();
    stream_ << "MulExpression: \n";
    ++tabs_num_;
    expression->first_->AcceptVisitor(this);
    expression->second_->AcceptVisitor(this);
    --tabs_num_;
}

void PrintTreeVisitor::Visit(DivExpression* expression) {
    PrintTabs();
    stream_ << "DivExpression: \n";
    ++tabs_num_;
    expression->first_->AcceptVisitor(this);
    expression->second_->AcceptVisitor(this);
    --tabs_num_;
}

void PrintTreeVisitor::Visit(SubstractExpression* expression) {
    PrintTabs();
    stream_ << "SubstractExpression: \n";
    ++tabs_num_;
    expression->first_->AcceptVisitor(this);
    expression->second_->AcceptVisitor(this);
    --tabs_num_;
}

void PrintTreeVisitor::Visit(IdentExpression* expression) {
    PrintTabs();
    stream_ << "Identifier: " << expression->ident_ << "\n";
}

void PrintTreeVisitor::Visit(NumExpression* expression) {
    PrintTabs();
    stream_ << "Number: " << expression->value_ << '\n';
}

void PrintTreeVisitor::Visit(Program* program) {
    PrintTabs();
    stream_ << "Program: \n";
    ++tabs_num_;
    program->AcceptVisitor(this);
    --tabs_num_;
}

void PrintTreeVisitor::PrintProgram(Program* program) {
    program->AcceptVisitor(this);
}

void PrintTreeVisitor::Visit(PrintStatement*) {
}

void PrintTreeVisitor::Visit(ReadStatement*) {
}

void PrintTreeVisitor::Visit(EqualExpression*) {
}

void PrintTreeVisitor::Visit(LessExpression*) {
}

void PrintTreeVisitor::Visit(GreaterExpression*) {
}

void PrintTreeVisitor::Visit(LessOrEqualExpression*) {
}

void PrintTreeVisitor::Visit(GreaterOrEqualExpression*) {
}

void PrintTreeVisitor::Visit(IfStatement*) {
}

void PrintTreeVisitor::Visit(Scope*) {
}

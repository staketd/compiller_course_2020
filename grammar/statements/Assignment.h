#ifndef MYCOMPILLER_ASSIGNMENT_H
#define MYCOMPILLER_ASSIGNMENT_H

#include <Expression.h>
#include <Statement.h>
#include <string>

class Assignment: public Statement {
public:
    Assignment(std::string variable, Expression* expression);
    void AcceptVisitor(BaseASTVisitor*) override;
    Expression* expression_;
    std::string variable_;
};

#endif //MYCOMPILLER_ASSIGNMENT_H

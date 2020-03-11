#ifndef MYCOMPILLER_ASSIGNMENT_H
#define MYCOMPILLER_ASSIGNMENT_H

#include <Expression.h>
#include <BaseClass.h>
#include <string>

class Assignment: public BaseClass {
public:
    Assignment(std::string variable, Expression* expression);
    void AcceptVisitor(BaseVisitor*) override;
    Expression* expression_;
    std::string variable_;
};


#endif //MYCOMPILLER_ASSIGNMENT_H


#ifndef MYCOMPILLER_VARIABLEDECLARATION_H
#define MYCOMPILLER_VARIABLEDECLARATION_H

#include <Statement.h>
#include <string>

class VariableDeclaration : public Statement {
public:
    explicit VariableDeclaration(std::string);
    void AcceptVisitor(BaseVisitor*) override;
public:
    std::string name_;
};


#endif //MYCOMPILLER_VARIABLEDECLARATION_H


#ifndef MYCOMPILLER_IFSTATEMENT_H
#define MYCOMPILLER_IFSTATEMENT_H
#include <Statement.h>
#include <Scope.h>

class IfStatement : public Statement {
public:
    IfStatement(Expression*, Scope*, Scope*);
    void AcceptVisitor(BaseVisitor*) override;

public:
    Expression* ifExpression_;
    Scope* then_;
    Scope* else_;
};


#endif //MYCOMPILLER_IFSTATEMENT_H

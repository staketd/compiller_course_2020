
#ifndef MYCOMPILLER_IFSTATEMENT_H
#define MYCOMPILLER_IFSTATEMENT_H
#include <Statement.h>
#include <StatementList.h>

class IfStatement : public Statement {
public:
    IfStatement(Expression*, StatementList*);
    void AcceptVisitor(BaseVisitor*) override;

public:
    Expression* ifExpression_;
    StatementList* statements_;
};


#endif //MYCOMPILLER_IFSTATEMENT_H

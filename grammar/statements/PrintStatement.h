
#ifndef MYCOMPILLER_PRINTSTATEMENT_H
#define MYCOMPILLER_PRINTSTATEMENT_H

#include <Statement.h>
#include <Expression.h>
#include <string>

class PrintStatement: public Statement {
public:
    explicit PrintStatement(Expression* );
    void AcceptVisitor(BaseASTVisitor*) override;

    Expression* expr_;
};


#endif  // MYCOMPILLER_IRPRINTSTATEMENT_H

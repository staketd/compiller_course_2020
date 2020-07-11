
#ifndef MYCOMPILLER_WHILESTATEMENT_H
#define MYCOMPILLER_WHILESTATEMENT_H
#include <Statement.h>
#include <ScopeLayer.h>

class WhileStatement : public Statement {
public:
    WhileStatement(Expression*, Scope*);
    void AcceptVisitor(BaseASTVisitor*);

public:
    Expression* check_expression_;
    Scope* scope_;
};


#endif //MYCOMPILLER_WHILESTATEMENT_H

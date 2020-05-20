
#ifndef MYCOMPILLER_SCOPE_H
#define MYCOMPILLER_SCOPE_H

#include <Statement.h>
#include <StatementList.h>

class Scope: public Statement {
public:
    explicit Scope(StatementList*);
    void AcceptVisitor(BaseVisitor*) override;

public:
    StatementList* statements_;
};


#endif //MYCOMPILLER_SCOPE_H

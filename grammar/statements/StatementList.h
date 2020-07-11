
#ifndef MYCOMPILLER_STATEMENTLIST_H
#define MYCOMPILLER_STATEMENTLIST_H

#include <Statement.h>
#include <vector>

class StatementList: public BaseASTClass {
public:
    void AddStatement(Statement*);
    void AcceptVisitor(BaseASTVisitor*) override;

    std::vector<Statement*> statements_;
};


#endif //MYCOMPILLER_STATEMENTLIST_H

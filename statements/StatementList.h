
#ifndef MYCOMPILLER_STATEMENTLIST_H
#define MYCOMPILLER_STATEMENTLIST_H

#include <Statement.h>
#include <vector>

class StatementList: BaseClass {
public:
    void AddStatement(Statement*);
    void AcceptVisitor(BaseVisitor*) override;

//private: # TODO add iterator
    std::vector<Statement*> statements_;
};


#endif //MYCOMPILLER_STATEMENTLIST_H

#ifndef MYCOMPILLER_PROGRAM_H
#define MYCOMPILLER_PROGRAM_H

#include <StatementList.h>
#include <Expression.h>

class Program: BaseClass {
public:
    explicit Program(StatementList*);
    void AcceptVisitor(BaseVisitor*) override;

private:
    StatementList* statements_;
};


#endif //MYCOMPILLER_PROGRAM_H

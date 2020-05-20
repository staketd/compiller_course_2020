#ifndef MYCOMPILLER_PROGRAM_H
#define MYCOMPILLER_PROGRAM_H

#include <FunctionList.h>
#include <Expression.h>

class Program: BaseASTClass {
public:
    explicit Program(FunctionList*);
    void AcceptVisitor(BaseVisitor*) override;

private:
    FunctionList* functions_;
};


#endif //MYCOMPILLER_PROGRAM_H

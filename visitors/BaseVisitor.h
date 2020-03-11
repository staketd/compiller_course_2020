
#ifndef MYCOMPILLER_BASEVISITOR_H
#define MYCOMPILLER_BASEVISITOR_H

#include "forward_decl.h"

class BaseVisitor {
public:
    virtual void Visit(AssignmentList*) = 0;
    virtual void Visit(Assignment*) = 0;
    virtual void Visit(AddExpression*) = 0;
    virtual void Visit(MulExpression*) = 0;
    virtual void Visit(DivExpression*) = 0;
    virtual void Visit(SubstractExpression*) = 0;
    virtual void Visit(IdentExpression*) = 0;
    virtual void Visit(NumExpression*) = 0;
    virtual void Visit(Program*) = 0;
};


#endif //MYCOMPILLER_BASEVISITOR_H

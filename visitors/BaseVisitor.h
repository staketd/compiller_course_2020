
#ifndef MYCOMPILLER_BASEVISITOR_H
#define MYCOMPILLER_BASEVISITOR_H

#include "include/forward_decl.h"

class BaseVisitor {
public:
    virtual void Visit(StatementList*) = 0;
    virtual void Visit(Assignment*) = 0;
    virtual void Visit(AddExpression*) = 0;
    virtual void Visit(MulExpression*) = 0;
    virtual void Visit(DivExpression*) = 0;
    virtual void Visit(SubstractExpression*) = 0;
    virtual void Visit(IdentExpression*) = 0;
    virtual void Visit(NumExpression*) = 0;
    virtual void Visit(ModuloExpression*) = 0;
    virtual void Visit(Program*) = 0;
    virtual void Visit(PrintStatement*) = 0;
    virtual void Visit(ReadStatement*) = 0;
    virtual void Visit(EqualExpression*) = 0;
    virtual void Visit(LessExpression*) = 0;
    virtual void Visit(GreaterExpression*) = 0;
    virtual void Visit(LessOrEqualExpression*) = 0;
    virtual void Visit(GreaterOrEqualExpression*) = 0;
    virtual void Visit(IfStatement*) = 0;
    virtual void Visit(Scope*) = 0;
    virtual void Visit(VariableDeclaration*) = 0;
    virtual void Visit(WhileStatement*) = 0;
};


#endif //MYCOMPILLER_BASEVISITOR_H

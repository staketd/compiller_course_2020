
#ifndef MYCOMPILLER_MODULOEXPRESSION_H
#define MYCOMPILLER_MODULOEXPRESSION_H
#include <BinaryExpression.h>

class ModuloExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;
    void AcceptVisitor(BaseVisitor*);
};


#endif //MYCOMPILLER_MODULOEXPRESSION_H

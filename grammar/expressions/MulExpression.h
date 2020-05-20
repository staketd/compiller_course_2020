#ifndef MYCOMPILLER_MULEXPRESSION_H
#define MYCOMPILLER_MULEXPRESSION_H

#include <BinaryExpression.h>

class MulExpression: public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    void AcceptVisitor(BaseVisitor*) override;
};

#endif //MYCOMPILLER_MULEXPRESSION_H

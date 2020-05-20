#ifndef MYCOMPILLER_DIVEXPRESSION_H
#define MYCOMPILLER_DIVEXPRESSION_H

#include <BinaryExpression.h>

class DivExpression: public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    void AcceptVisitor(BaseVisitor*) override;
};

#endif //MYCOMPILLER_DIVEXPRESSION_H

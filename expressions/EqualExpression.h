
#ifndef MYCOMPILLER_EQUALEXPRESSION_H
#define MYCOMPILLER_EQUALEXPRESSION_H
#include <BinaryExpression.h>

class EqualExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    void AcceptVisitor(BaseVisitor*) override;

public:
};


#endif //MYCOMPILLER_EQUALEXPRESSION_H

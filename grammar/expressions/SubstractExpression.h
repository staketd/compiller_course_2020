
#ifndef MYCOMPILLER_SUBSTRACTEXPRESSION_H
#define MYCOMPILLER_SUBSTRACTEXPRESSION_H

#include <BinaryExpression.h>

class SubstractExpression: public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    void AcceptVisitor(BaseASTVisitor*) override;
};


#endif //MYCOMPILLER_SUBSTRACTEXPRESSION_H

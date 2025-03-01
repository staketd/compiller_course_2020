
#ifndef MYCOMPILLER_GREATEREXPRESSION_H
#define MYCOMPILLER_GREATEREXPRESSION_H

#include <BinaryExpression.h>

class GreaterExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    void AcceptVisitor(BaseASTVisitor*) override;
};


#endif //MYCOMPILLER_GREATEREXPRESSION_H

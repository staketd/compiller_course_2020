
#ifndef MYCOMPILLER_LESSOREQUALEXPRESSION_H
#define MYCOMPILLER_LESSOREQUALEXPRESSION_H

#include <BinaryExpression.h>

class LessOrEqualExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    void AcceptVisitor(BaseASTVisitor*) override;
};


#endif //MYCOMPILLER_LESSOREQUALEXPRESSION_H

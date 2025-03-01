
#ifndef MYCOMPILLER_LESSEXPRESSION_H
#define MYCOMPILLER_LESSEXPRESSION_H

#include <BinaryExpression.h>

class LessExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    void AcceptVisitor(BaseASTVisitor*) override;
};


#endif //MYCOMPILLER_LESSEXPRESSION_H

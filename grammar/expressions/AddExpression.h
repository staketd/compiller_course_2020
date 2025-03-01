#ifndef MYCOMPILLER_ADDEXPRESSION_H
#define MYCOMPILLER_ADDEXPRESSION_H

#include <BinaryExpression.h>

class AddExpression: public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    void AcceptVisitor(BaseASTVisitor*) override;
};

#endif //MYCOMPILLER_ADDEXPRESSION_H

#ifndef MYCOMPILLER_NUMEXPRESSION_H
#define MYCOMPILLER_NUMEXPRESSION_H

#include "Expression.h"

class NumExpression: public Expression {
public:
    NumExpression(int value);
    void AcceptVisitor(BaseASTVisitor*) override;

    int value_;
};

#endif //MYCOMPILLER_NUMEXPRESSION_H

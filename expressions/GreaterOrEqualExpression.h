
#ifndef MYCOMPILLER_GREATEROREQUALEXPRESSION_H
#define MYCOMPILLER_GREATEROREQUALEXPRESSION_H

#include <BinaryExpression.h>

class GreaterOrEqualExpression : public BinaryExpression {
public:
    using BinaryExpression::BinaryExpression;

    void AcceptVisitor(BaseVisitor*) override;

};


#endif //MYCOMPILLER_GREATEROREQUALEXPRESSION_H

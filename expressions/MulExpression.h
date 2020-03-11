#ifndef MYCOMPILLER_MULEXPRESSION_H
#define MYCOMPILLER_MULEXPRESSION_H

#include "Expression.h"

class MulExpression: public Expression {
public:
    MulExpression(Expression*, Expression*);
    void AcceptVisitor(BaseVisitor*) override;
    [[nodiscard]] int eval() const override;
    Expression* first_;
    Expression* second_;
};

#endif //MYCOMPILLER_MULEXPRESSION_H

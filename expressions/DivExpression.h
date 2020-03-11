#ifndef MYCOMPILLER_DIVEXPRESSION_H
#define MYCOMPILLER_DIVEXPRESSION_H

#include "Expression.h"

class DivExpression: public Expression {
public:
    DivExpression(Expression*, Expression*);
    [[nodiscard]] int eval() const override;
    void AcceptVisitor(BaseVisitor*) override;
    Expression* first_;
    Expression* second_;
};

#endif //MYCOMPILLER_DIVEXPRESSION_H

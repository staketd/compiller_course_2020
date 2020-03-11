
#ifndef MYCOMPILLER_SUBSTRACTEXPRESSION_H
#define MYCOMPILLER_SUBSTRACTEXPRESSION_H

#include "Expression.h"

class SubstractExpression: public Expression {
public:
    SubstractExpression(Expression*, Expression*);
    [[nodiscard]] int eval() const override;
    void AcceptVisitor(BaseVisitor*) override;
    Expression* first_;
    Expression* second_;
};


#endif //MYCOMPILLER_SUBSTRACTEXPRESSION_H

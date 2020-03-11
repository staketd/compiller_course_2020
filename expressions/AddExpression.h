#ifndef MYCOMPILLER_ADDEXPRESSION_H
#define MYCOMPILLER_ADDEXPRESSION_H

#include "Expression.h"

class AddExpression: public Expression {
public:
    AddExpression(Expression* first, Expression* second);
    [[nodiscard]] int eval() const override;
    void AcceptVisitor(BaseVisitor*) override;
    Expression* first_;
    Expression* second_;
};

#endif //MYCOMPILLER_ADDEXPRESSION_H

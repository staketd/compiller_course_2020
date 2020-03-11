#ifndef MYCOMPILLER_IDENTEXPRESSION_H
#define MYCOMPILLER_IDENTEXPRESSION_H

#include <string>
#include "Expression.h"

class IdentExpression: public Expression {
public:
    IdentExpression(std::string ident);
    int eval() const override;
    void AcceptVisitor(BaseVisitor*) override;
    std::string ident_;
};


#endif //MYCOMPILLER_IDENTEXPRESSION_H

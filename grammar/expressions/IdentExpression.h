#ifndef MYCOMPILLER_IDENTEXPRESSION_H
#define MYCOMPILLER_IDENTEXPRESSION_H

#include <string>
#include "Expression.h"

class IdentExpression: public Expression {
public:
    IdentExpression(std::string ident);
    void AcceptVisitor(BaseVisitor*) override;
    std::string name_;
};


#endif //MYCOMPILLER_IDENTEXPRESSION_H

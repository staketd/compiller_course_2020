
#ifndef MYCOMPILLER_BINARYEXPRESSION_H
#define MYCOMPILLER_BINARYEXPRESSION_H
#include <Expression.h>

class BinaryExpression : public Expression {
public:
    BinaryExpression(Expression*, Expression*);

public:
    Expression* first_;
    Expression* second_;
};


#endif //MYCOMPILLER_BINARYEXPRESSION_H

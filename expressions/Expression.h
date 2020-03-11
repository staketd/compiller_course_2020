#ifndef MYCOMPILLER_EXPRESSION_H
#define MYCOMPILLER_EXPRESSION_H

#include <BaseClass.h>

class Expression: public BaseClass {
public:
    virtual int eval() const = 0;
private:
};


#endif //MYCOMPILLER_EXPRESSION_H

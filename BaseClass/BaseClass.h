
#ifndef MYCOMPILLER_BASECLASS_H
#define MYCOMPILLER_BASECLASS_H

#include <BaseVisitor.h>

class BaseClass {
public:
    virtual void AcceptVisitor(BaseVisitor*) = 0;
    virtual ~BaseClass() = default;
};


#endif //MYCOMPILLER_BASECLASS_H

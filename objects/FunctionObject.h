
#ifndef MYCOMPILLER_FUNCTIONOBJECT_H
#define MYCOMPILLER_FUNCTIONOBJECT_H

#include <BaseObject.h>
#include <vector>
#include <string>

class FunctionObject : public BaseObject {
public:
    int ToInt() override;
    bool IsFunction() override;

public:
    explicit FunctionObject();
};


#endif  // MYCOMPILLER_FUNCTIONOBJECT_H

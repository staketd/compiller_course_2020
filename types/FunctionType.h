
#ifndef MYCOMPILLER_FUNCTIONTYPE_H
#define MYCOMPILLER_FUNCTIONTYPE_H

#include <BaseType.h>
#include <vector>
#include <string>

class FunctionType : public BaseType {
public:
    int ToInt() override;
    bool IsFunction() override;
    BaseType* GetType() override;

public:
    explicit FunctionType();
};


#endif //MYCOMPILLER_FUNCTIONTYPE_H


#ifndef MYCOMPILLER_FUNCTIONTYPE_H
#define MYCOMPILLER_FUNCTIONTYPE_H

#include <BaseObject.h>
#include <vector>
#include <string>

class FunctionType : public BaseObject {
public:
    int ToInt() override;

public:
    explicit FunctionType(std::vector<std::string> );
    std::vector<BaseObject*> arguments_;
    std::vector<std::string> arguments_names_;
    BaseObject* return_type_;
};


#endif //MYCOMPILLER_FUNCTIONTYPE_H

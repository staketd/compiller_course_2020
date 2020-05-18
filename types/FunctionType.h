
#ifndef MYCOMPILLER_FUNCTIONTYPE_H
#define MYCOMPILLER_FUNCTIONTYPE_H

#include <BaseType.h>
#include <vector>
#include <string>

class FunctionType : public BaseType {
public:
    int ToInt() override;
    bool IsFunction() override;

public:
    explicit FunctionType(std::vector<std::string> );
    std::vector<BaseType*> arguments_;
    std::vector<std::string> arguments_names_;
    BaseType* return_type_;
};


#endif //MYCOMPILLER_FUNCTIONTYPE_H

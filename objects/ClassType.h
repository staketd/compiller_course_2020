
#ifndef MYCOMPILLER_CLASSTYPE_H
#define MYCOMPILLER_CLASSTYPE_H

#include <BaseObject.h>
#include <FunctionType.h>

class ClassType : public BaseObject {
public:
    int ToInt() override;
public:
    std::vector<FunctionType*> methods_;
    std::vector<BaseObject*> fields_;
    std::vector<std::string> methods_names_;
    std::vector<std::string> fields_names_;
};


#endif //MYCOMPILLER_CLASSTYPE_H

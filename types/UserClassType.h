
#ifndef MYCOMPILLER_CLASSTYPE_H
#define MYCOMPILLER_CLASSTYPE_H

#include <BaseType.h>
#include <FunctionType.h>

class UserClassType : public BaseType {
 public:
  int ToInt() override;
  bool IsUserClass() override;

 public:
  std::string name_;
  std::vector<FunctionType*> methods_;
  std::vector<BaseType*> fields_;
  std::vector<std::string> methods_names_;
  std::vector<std::string> fields_names_;
};

#endif  // MYCOMPILLER_CLASSTYPE_H

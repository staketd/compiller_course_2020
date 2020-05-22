
#ifndef MYCOMPILLER_CLASSTYPE_H
#define MYCOMPILLER_CLASSTYPE_H
#include <BaseType.h>

class ClassType : public BaseType {
 public:
  ClassType(const std::string&);
  bool IsSameWith(std::shared_ptr<BaseType>) override;
  std::string TypeName() override;

 public:
  std::string class_name_;
};
#endif  // MYCOMPILLER_CLASSTYPE_H

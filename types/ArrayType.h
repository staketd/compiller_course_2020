
#ifndef MYCOMPILLER_ARRAYTYPE_H
#define MYCOMPILLER_ARRAYTYPE_H
#include <BaseType.h>

class ArrayType : public BaseType {
 public:
  ArrayType(std::shared_ptr<BaseType>);
  std::string TypeName() override;

 public:
  std::shared_ptr<BaseType> array_type_;
};

#endif  // MYCOMPILLER_ARRAYTYPE_H

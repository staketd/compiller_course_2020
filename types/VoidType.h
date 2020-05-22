
#ifndef MYCOMPILLER_VOIDTYPE_H
#define MYCOMPILLER_VOIDTYPE_H
#include <BaseType.h>

class VoidType : public BaseType {
 public:
  VoidType();
  std::string TypeName() override;
};

#endif  // MYCOMPILLER_VOIDTYPE_H

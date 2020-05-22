
#ifndef MYCOMPILLER_BOOLTYPE_H
#define MYCOMPILLER_BOOLTYPE_H
#include <BaseType.h>

class BoolType : public BaseType {
 public:
  BoolType();
  std::string TypeName() override;
};

#endif  // MYCOMPILLER_BOOLTYPE_H

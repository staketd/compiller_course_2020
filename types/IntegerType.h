
#ifndef MYCOMPILLER_INTEGERTYPE_H
#define MYCOMPILLER_INTEGERTYPE_H
#include <BaseType.h>
class IntegerType : public BaseType {
 public:
  IntegerType();
  std::string TypeName() override;
};

#endif  // MYCOMPILLER_INTEGERTYPE_H


#ifndef MYCOMPILLER_OBJECTS_BOOL_H_
#define MYCOMPILLER_OBJECTS_BOOL_H_
#include <PrimitiveType.h>

class BoolType : public PrimitiveType {
 public:
  BoolType();
  BoolType(bool);
  bool IsBool() override;
  int ToInt() override;
  BaseType* GetType() override;

 private:
  bool value_;
};

#endif  // MYCOMPILLER_OBJECTS_BOOL_H_

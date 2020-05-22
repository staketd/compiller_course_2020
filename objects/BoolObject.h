
#ifndef MYCOMPILLER_OBJECTS_BOOL_H_
#define MYCOMPILLER_OBJECTS_BOOL_H_
#include <PrimitiveObject.h>

class BoolObject : public PrimitiveObject {
 public:
  BoolObject();
  BoolObject(bool);
  bool IsBool() override;
  int ToInt() override;

 private:
  bool value_;
};

#endif  // MYCOMPILLER_OBJECTS_BOOL_H_

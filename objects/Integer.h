
#ifndef MYCOMPILLER_INTEGER_H
#define MYCOMPILLER_INTEGER_H

#include <PrimitiveObject.h>

class Integer : public PrimitiveObject {
 public:
  Integer();
  Integer(int val);
  int ToInt() override;
  bool IsInteger() override;

 private:
  int value_;
};

#endif  // MYCOMPILLER_INTEGER_H

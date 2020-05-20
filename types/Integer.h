
#ifndef MYCOMPILLER_INTEGER_H
#define MYCOMPILLER_INTEGER_H

#include <PrimitiveType.h>

class Integer : public PrimitiveType {
 public:
  Integer();
  Integer(int val);
  int ToInt() override;
  bool IsInteger() override;
  BaseType* GetType() override;

 private:
  int value_;
};

#endif  // MYCOMPILLER_INTEGER_H

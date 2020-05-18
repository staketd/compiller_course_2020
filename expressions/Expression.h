#ifndef MYCOMPILLER_EXPRESSION_H
#define MYCOMPILLER_EXPRESSION_H

#include <BaseClass.h>
#include <BaseType.h>

class Expression: public BaseClass {
 public:
  virtual BaseType*& Type() {
    return type_;
  }

 private:
  BaseType* type_;
};

#endif //MYCOMPILLER_EXPRESSION_H

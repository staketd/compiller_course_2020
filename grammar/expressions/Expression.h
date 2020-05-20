#ifndef MYCOMPILLER_EXPRESSION_H
#define MYCOMPILLER_EXPRESSION_H

#include <BaseASTClass.h>
#include <BaseType.h>

class Expression: public BaseASTClass {
 public:
  virtual BaseType*& Type() {
    return type_;
  }

 private:
  BaseType* type_;
};

#endif //MYCOMPILLER_EXPRESSION_H

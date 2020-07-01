
#ifndef MYCOMPILLER_BASEASTCLASS_H
#define MYCOMPILLER_BASEASTCLASS_H

#include <BaseVisitor.h>
#include <location.hh>

class BaseASTClass {
 public:
  virtual void AcceptVisitor(BaseVisitor*) = 0;
  virtual ~BaseASTClass() = default;
 public:
  yy::location loc;
};


#endif  // MYCOMPILLER_BASEASTCLASS_H

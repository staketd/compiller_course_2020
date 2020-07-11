
#ifndef MYCOMPILLER_BASEASTCLASS_H
#define MYCOMPILLER_BASEASTCLASS_H

#include <BaseVisitors.h>
#include <location.hh>

class BaseASTClass {
 public:
  virtual void AcceptVisitor(BaseASTVisitor*) = 0;
  virtual ~BaseASTClass() = default;
 public:
  yy::location loc;
};


#endif  // MYCOMPILLER_BASEASTCLASS_H

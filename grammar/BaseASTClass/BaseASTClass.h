
#ifndef MYCOMPILLER_BASEASTCLASS_H
#define MYCOMPILLER_BASEASTCLASS_H

#include <BaseVisitor.h>

class BaseASTClass {
 public:
  virtual void AcceptVisitor(BaseVisitor*) = 0;
  virtual ~BaseASTClass() = default;
};

#endif  // MYCOMPILLER_BASEASTCLASS_H

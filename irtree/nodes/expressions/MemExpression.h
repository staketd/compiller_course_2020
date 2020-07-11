
#ifndef MYCOMPILLER_MEMEXPRESSION_H
#define MYCOMPILLER_MEMEXPRESSION_H
#include "IRExpression.h"

namespace ir_tree {

class MemExpression : public ir_tree::IRExpression {
 public:
  MemExpression(IRExpression* expression);
  void AcceptVisitor(ir_tree::BaseIRVisitor*);

 public:
  IRExpression* expression_;
};

}
#endif  // MYCOMPILLER_MEMEXPRESSION_H

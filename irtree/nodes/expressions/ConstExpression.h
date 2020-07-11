
#ifndef MYCOMPILLER_CONSTEXPRESSION_H
#define MYCOMPILLER_CONSTEXPRESSION_H

#include "IRExpression.h"

namespace ir_tree {

class ConstExpression : public ir_tree::IRExpression {
 public:
  ConstExpression(int);
  int Value();

  void AcceptVisitor(ir_tree::BaseIRVisitor*) override;

 private:
  int value_;
};

}
#endif  // MYCOMPILLER_CONSTEXPRESSION_H


#ifndef MYCOMPILLER_ESEQEXPRESSION_H
#define MYCOMPILLER_ESEQEXPRESSION_H

#include "IRExpression.h"
#include "../statements/IRStatement.h"

namespace ir_tree {

class EseqExpression : public ir_tree::IRExpression {
 public:
  EseqExpression(ir_tree::IRStatement*, ir_tree::IRExpression*);
  void AcceptVisitor(ir_tree::BaseIRVisitor*) override;

 public:
  IRStatement* statement_;
  IRExpression* expression_;
};

}
#endif  // MYCOMPILLER_ESEQEXPRESSION_H

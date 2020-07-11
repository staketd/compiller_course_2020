
#ifndef MYCOMPILLER_NAMEEXPRESSION_H
#define MYCOMPILLER_NAMEEXPRESSION_H
#include "IRExpression.h"
#include <Label.h>
namespace ir_tree {

class NameExpression : public ir_tree::IRExpression {
 public:
  NameExpression(Label);
  void AcceptVisitor(ir_tree::BaseIRVisitor*);

 public:
  Label label_;
};

}  // namespace ir_tree

#endif  // MYCOMPILLER_NAMEEXPRESSION_H

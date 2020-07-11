
#ifndef MYCOMPILLER_JUMPSTATEMENT_H
#define MYCOMPILLER_JUMPSTATEMENT_H
#include "IRStatement.h"
#include <Label.h>
namespace ir_tree {

class JumpStatement : public ir_tree::IRStatement {
 public:
  JumpStatement(Label);
  void AcceptVisitor(ir_tree::BaseIRVisitor*) override;

 public:
  Label label_;
};

}  // namespace ir_tree
#endif  // MYCOMPILLER_JUMPSTATEMENT_H

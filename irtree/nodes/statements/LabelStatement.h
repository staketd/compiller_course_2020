
#ifndef MYCOMPILLER_LABELSTATEMENT_H
#define MYCOMPILLER_LABELSTATEMENT_H
#include "IRStatement.h"
#include <Label.h>
namespace ir_tree {

class LabelStatement : public ir_tree::IRStatement {
 public:
  LabelStatement(ir_tree::Label);
  void AcceptVisitor(ir_tree::BaseIRVisitor*) override;

 public:
  Label label_;
};

}  // namespace ir_tree
#endif  // MYCOMPILLER_LABELSTATEMENT_H

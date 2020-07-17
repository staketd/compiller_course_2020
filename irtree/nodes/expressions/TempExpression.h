
#ifndef MYCOMPILLER_TEMPEXPRESSION_H
#define MYCOMPILLER_TEMPEXPRESSION_H
#include "IRExpression.h"
#include <Temp.h>

namespace ir_tree {

class TempExpression : public ir_tree::IRExpression {
 public:
  explicit TempExpression(const ir_tree::Temp&);
  void AcceptVisitor(ir_tree::BaseIRVisitor*) override;

  IRNodeType GetType();

 public:
  Temp temp_;
};

}  // namespace ir_tree
#endif  // MYCOMPILLER_TEMPEXPRESSION_H

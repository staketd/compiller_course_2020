
#ifndef MYCOMPILLER_EXPSTATEMENT_H
#define MYCOMPILLER_EXPSTATEMENT_H
#include "IRStatement.h"
#include "../expressions/IRExpression.h"

namespace ir_tree {

class ExpStatement : public ir_tree::IRStatement {
 public:
  ExpStatement(ir_tree::IRExpression*);
  void AcceptVisitor(ir_tree::BaseIRVisitor*) override;

 public:
  ir_tree::IRExpression* expression_;
};

}  // namespace ir_tree
#endif  // MYCOMPILLER_EXPSTATEMENT_H

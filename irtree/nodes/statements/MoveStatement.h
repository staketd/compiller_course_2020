
#ifndef MYCOMPILLER_MOVESTATEMENT_H
#define MYCOMPILLER_MOVESTATEMENT_H
#include "IRStatement.h"
#include "../expressions/IRExpression.h"
namespace ir_tree {

class MoveStatement : public ir_tree::IRStatement {
 public:
  MoveStatement(ir_tree::IRExpression* source, ir_tree::IRExpression* dest);
  void AcceptVisitor(ir_tree::BaseIRVisitor*) override;

 public:
  ir_tree::IRExpression* source_;
  ir_tree::IRExpression* target_;
};
}  // namespace ir_tree
#endif  // MYCOMPILLER_MOVESTATEMENT_H

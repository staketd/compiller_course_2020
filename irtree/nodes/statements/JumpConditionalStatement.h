
#ifndef MYCOMPILLER_JUMPCONDITIONALSTATEMENT_H
#define MYCOMPILLER_JUMPCONDITIONALSTATEMENT_H
#include "IRStatement.h"
#include <LogicOperatorType.h>
#include "../expressions/IRExpression.h"
#include <Label.h>

namespace ir_tree {

class JumpConditionalStatement : public ir_tree::IRStatement {
 public:
  JumpConditionalStatement(
        LogicOperatorType,
        ir_tree::IRExpression*,
        ir_tree::IRExpression*,
        ir_tree::Label,
        ir_tree::Label
      );
  void AcceptVisitor(ir_tree::BaseIRVisitor*) override;

  IRNodeType GetType() override;

 public:
  LogicOperatorType operator_;
  ir_tree::IRExpression* left_;
  ir_tree::IRExpression* right_;
  ir_tree::Label label_true_;
  ir_tree::Label label_false_;
};

}  // namespace ir_tree

#endif  // MYCOMPILLER_JUMPCONDITIONALSTATEMENT_H


#ifndef MYCOMPILLER_CALLEXPRESSION_H
#define MYCOMPILLER_CALLEXPRESSION_H

#include <irtree/nodes/expressions/IRExpression.h>
#include <ExpressionList.h>

namespace ir_tree {

class CallExpression : public IRExpression {
 public:
  CallExpression(ir_tree::IRExpression*, ExpressionList*, bool);
  void AcceptVisitor(ir_tree::BaseIRVisitor*);
  IRNodeType GetType() override;

 public:
  IRExpression* function_name_;
  ExpressionList* args_;
  bool has_return_value_;
};

}
#endif  // MYCOMPILLER_CALLEXPRESSION_H

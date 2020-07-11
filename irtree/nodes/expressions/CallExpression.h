
#ifndef MYCOMPILLER_CALLEXPRESSION_H
#define MYCOMPILLER_CALLEXPRESSION_H

#include <irtree/nodes/expressions/IRExpression.h>
#include <ExpressionList.h>

namespace ir_tree {

class CallExpression : public IRExpression {
 public:
  CallExpression(ir_tree::IRExpression*, ExpressionList*);
  void AcceptVisitor(ir_tree::BaseIRVisitor*);

 public:
  IRExpression* function_name_;
  ExpressionList* args_;
};

}
#endif  // MYCOMPILLER_CALLEXPRESSION_H

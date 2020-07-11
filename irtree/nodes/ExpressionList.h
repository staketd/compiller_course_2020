
#ifndef MYCOMPILLER_EXPRESSIONLIST_H
#define MYCOMPILLER_EXPRESSIONLIST_H
#include <BaseIRNode.h>
#include <IRExpression.h>
#include <vector>
namespace ir_tree {

class ExpressionList : public ir_tree::BaseIRNode {
 public:
  ExpressionList(std::vector<IRExpression*>);
  void AcceptVisitor(ir_tree::BaseIRVisitor*);

 public:
  std::vector<IRExpression*> expressions_;
};

}
#endif  // MYCOMPILLER_EXPRESSIONLIST_H

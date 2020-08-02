
#ifndef MYCOMPILLER_ALLOCEXPRESSION_H
#define MYCOMPILLER_ALLOCEXPRESSION_H
#include <IRExpression.h>
namespace ir_tree {
class AllocExpression : public IRExpression {
 public:
  AllocExpression(size_t);
  void AcceptVisitor(ir_tree::BaseIRVisitor*) override;
  IRNodeType GetType() override;

 public:
  size_t size_;
};
}  // namespace ir_tree
#endif  // MYCOMPILLER_ALLOCEXPRESSION_H

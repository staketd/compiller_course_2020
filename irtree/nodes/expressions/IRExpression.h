
#ifndef MYCOMPILLER_IREXPRESSION_H
#define MYCOMPILLER_IREXPRESSION_H

#include <BaseIRNode.h>

namespace ir_tree {

class IRExpression : public ir_tree::BaseIRNode {
 public:
  virtual ~IRExpression() = default;
};

}  // namespace ir_tree

#endif  // MYCOMPILLER_IREXPRESSION_H

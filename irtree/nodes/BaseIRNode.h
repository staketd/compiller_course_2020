
#ifndef MYCOMPILLER_BASEIRNODE_H
#define MYCOMPILLER_BASEIRNODE_H
#include <BaseVisitors.h>

namespace ir_tree {

class BaseIRNode {
 public:
  virtual ~BaseIRNode() = default;
  virtual void AcceptVisitor(ir_tree::BaseIRVisitor*) = 0;
};

}  // namespace ir_tree

#endif  // MYCOMPILLER_BASEIRNODE_H

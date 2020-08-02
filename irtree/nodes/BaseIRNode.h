
#ifndef MYCOMPILLER_BASEIRNODE_H
#define MYCOMPILLER_BASEIRNODE_H
#include <BaseVisitors.h>
#include <string>
namespace ir_tree {

enum class IRNodeType {
  BinOp,
  Call,
  Const,
  Eseq,
  Mem,
  Name,
  Temp,
  Exp,
  Print,
  CJump,
  Jump,
  Label,
  Move,
  Seq,
  ExpList,
  Alloc,
};

class BaseIRNode {
 public:
  virtual ~BaseIRNode() = default;
  virtual IRNodeType GetType() = 0;
  virtual void AcceptVisitor(ir_tree::BaseIRVisitor*) = 0;
};


}  // namespace ir_tree

#endif  // MYCOMPILLER_BASEIRNODE_H

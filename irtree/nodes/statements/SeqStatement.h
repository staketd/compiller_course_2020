
#ifndef MYCOMPILLER_SEQSTATEMENT_H
#define MYCOMPILLER_SEQSTATEMENT_H
#include "IRStatement.h"
namespace ir_tree {
class SeqStatement : public ir_tree::IRStatement {
 public:
  SeqStatement(IRStatement*, IRStatement*);
  void AcceptVisitor(ir_tree::BaseIRVisitor*) override;

  IRNodeType GetType() override;

 public:
  IRStatement* first_;
  IRStatement* second_;
};
}  // namespace ir_tree

#endif  // MYCOMPILLER_SEQSTATEMENT_H

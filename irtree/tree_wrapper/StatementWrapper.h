
#ifndef MYCOMPILLER_STATEMENTWRAPPER_H
#define MYCOMPILLER_STATEMENTWRAPPER_H
#include "SubtreeWrapper.h"
namespace ir_tree {
class StatementWrapper : public SubtreeWrapper {
 public:
  StatementWrapper(ir_tree::IRStatement*);
  ir_tree::IRExpression* ToExpression() override;
  ir_tree::IRStatement* ToStatement() override;
  ir_tree::IRStatement* ToConditional(Label, Label) override;

 public:
  IRStatement* statement_;
};
}  // namespace ir_tree

#endif  // MYCOMPILLER_STATEMENTWRAPPER_H

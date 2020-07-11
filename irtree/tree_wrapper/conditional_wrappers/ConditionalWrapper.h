
#ifndef MYCOMPILLER_CONDITIONALWRAPPER_H
#define MYCOMPILLER_CONDITIONALWRAPPER_H
#include <SubtreeWrapper.h>

namespace ir_tree {
class ConditionalWrapper : public SubtreeWrapper {
  ir_tree::IRExpression* ToExpression() override;
  ir_tree::IRStatement* ToStatement() override;
};
}  // namespace ir_tree

#endif  // MYCOMPILLER_CONDITIONALWRAPPER_H

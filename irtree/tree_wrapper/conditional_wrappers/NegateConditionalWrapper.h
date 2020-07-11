
#ifndef MYCOMPILLER_NEGATECONDITIONALWRAPPER_H
#define MYCOMPILLER_NEGATECONDITIONALWRAPPER_H
#include <ConditionalWrapper.h>
namespace ir_tree {
class NegateConditionalWrapper : public ConditionalWrapper {
 public:
  NegateConditionalWrapper(SubtreeWrapper*);
  ir_tree::IRStatement* ToConditional(Label, Label) override;

 private:
  SubtreeWrapper* wrapper_;
};
}  // namespace ir_tree
#endif  // MYCOMPILLER_NEGATECONDITIONALWRAPPER_H

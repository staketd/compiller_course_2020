
#ifndef MYCOMPILLER_ANDCONDITIONALWRAPPER_H
#define MYCOMPILLER_ANDCONDITIONALWRAPPER_H
#include <ConditionalWrapper.h>
namespace ir_tree {
class AndConditionalWrapper : public ConditionalWrapper {
 public:
  AndConditionalWrapper(SubtreeWrapper* first, SubtreeWrapper* second);
  IRStatement* ToConditional(Label, Label) override;

 private:
  SubtreeWrapper* first_;
  SubtreeWrapper* second_;
};
}  // namespace ir_tree
#endif  // MYCOMPILLER_ANDCONDITIONALWRAPPER_H


#ifndef MYCOMPILLER_ORCONDITIONALWRAPPER_H
#define MYCOMPILLER_ORCONDITIONALWRAPPER_H
#include <ConditionalWrapper.h>
namespace ir_tree {
class OrConditionalWrapper : public ConditionalWrapper {
 public:
  OrConditionalWrapper(SubtreeWrapper*, SubtreeWrapper*);
  ir_tree::IRStatement* ToConditional(Label, Label) override;

 private:
  SubtreeWrapper* first_;
  SubtreeWrapper* second_;
};
}  // namespace ir_tree
#endif  // MYCOMPILLER_ORCONDITIONALWRAPPER_H

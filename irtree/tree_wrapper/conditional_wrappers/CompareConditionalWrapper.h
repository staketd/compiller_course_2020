
#ifndef MYCOMPILLER_COMPARECONDITIONALWRAPPER_H
#define MYCOMPILLER_COMPARECONDITIONALWRAPPER_H
#include <ConditionalWrapper.h>
#include <LogicOperatorType.h>
#include "../nodes/expressions/IRExpression.h"
namespace ir_tree {
class CompareConditionalWrapper : public ConditionalWrapper {
 public:
  CompareConditionalWrapper(LogicOperatorType, ir_tree::IRExpression*, ir_tree::IRExpression*);
  IRStatement* ToConditional(Label, Label) override;

 private:
  LogicOperatorType operator_;
  ir_tree::IRExpression* first_;
  ir_tree::IRExpression* second_;
};
}  // namespace ir_tree
#endif  // MYCOMPILLER_COMPARECONDITIONALWRAPPER_H


#ifndef MYCOMPILLER_SUBTREEWRAPPER_H
#define MYCOMPILLER_SUBTREEWRAPPER_H
#include "../nodes/expressions/IRExpression.h"
#include "../nodes/statements/IRStatement.h"
#include <Label.h>

namespace ir_tree {
class SubtreeWrapper {
 public:
  virtual IRExpression* ToExpression() = 0;
  virtual IRStatement* ToStatement() = 0;
  virtual IRStatement* ToConditional(Label, Label) = 0;
};
}  // namespace ir_tree

#endif  // MYCOMPILLER_SUBTREEWRAPPER_H

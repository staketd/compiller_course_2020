
#ifndef MYCOMPILLER_EXPRESSIONWRAPPER_H
#define MYCOMPILLER_EXPRESSIONWRAPPER_H
#include "../nodes/expressions/IRExpression.h"
#include "../nodes/statements/IRStatement.h"
#include "SubtreeWrapper.h"
namespace ir_tree {

class ExpressionWrapper : public ir_tree::SubtreeWrapper {
 public:
  ExpressionWrapper(ir_tree::IRExpression*);
  ir_tree::IRExpression* ToExpression() override;
  ir_tree::IRStatement* ToStatement() override;
  ir_tree::IRStatement* ToConditional(Label, Label) override;

 public:
  IRExpression* expression_;
};
}  // namespace ir_tree
#endif  // MYCOMPILLER_EXPRESSIONWRAPPER_H

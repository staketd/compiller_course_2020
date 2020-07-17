
#ifndef MYCOMPILLER_IRUNION_H
#define MYCOMPILLER_IRUNION_H
#include <IRExpression.h>
#include <IRStatement.h>
namespace ir_tree {
struct IRUnion {
  IRExpression* expression_;
  IRStatement* statement_;
  ExpressionList* expression_list_;
};
}  // namespace ir_tree

#endif  // MYCOMPILLER_IRUNION_H


#ifndef MYCOMPILLER_ADDRESS_H
#define MYCOMPILLER_ADDRESS_H
#include <IRExpression.h>
namespace ir_tree {
class Address {
 public:
  virtual ir_tree::IRExpression* ToExpression() = 0;
};
}

#endif  // MYCOMPILLER_ADDRESS_H

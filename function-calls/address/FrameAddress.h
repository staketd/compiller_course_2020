
#ifndef MYCOMPILLER_FRAMEADDRESS_H
#define MYCOMPILLER_FRAMEADDRESS_H
#include <Address.h>
namespace ir_tree {
class FrameAddress : public Address {
 public:
  FrameAddress(Address*, int);
  IRExpression* ToExpression() override;

 private:
  Address* frame_addres_;
  int offset_;
};
}  // namespace ir_tree
#endif  // MYCOMPILLER_FRAMEADDRESS_H

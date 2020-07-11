
#ifndef MYCOMPILLER_REGADDRESS_H
#define MYCOMPILLER_REGADDRESS_H
#include <Address.h>
#include <Temp.h>
namespace ir_tree {
class RegAddress : public Address {
 public:
  RegAddress(const Temp&);
  IRExpression* ToExpression() override;

 private:
  Temp temp_;
};
}  // namespace ir_tree
#endif  // MYCOMPILLER_REGADDRESS_H


#ifndef MYCOMPILLER_IRPRINTSTATEMENT_H
#define MYCOMPILLER_IRPRINTSTATEMENT_H
#include <IRStatement.h>
#include <IRExpression.h>

namespace ir_tree {
class IRPrintStatement : public IRStatement {
 public:
  IRPrintStatement(IRExpression*);
  void AcceptVisitor(ir_tree::BaseIRVisitor*) override;

 public:
  IRExpression* expression_;
};
}  // namespace ir_tree

#endif  // MYCOMPILLER_IRPRINTSTATEMENT_H

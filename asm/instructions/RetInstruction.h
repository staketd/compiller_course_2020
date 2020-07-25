
#ifndef MYCOMPILLER_RETINSTRUCTION_H
#define MYCOMPILLER_RETINSTRUCTION_H
#include <AsmInstruction.h>
class RetInstruction : public AsmInstruction {
 public:
  RetInstruction() = default;
  void Print(std::ostream&) override;
};

#endif  // MYCOMPILLER_RETINSTRUCTION_H

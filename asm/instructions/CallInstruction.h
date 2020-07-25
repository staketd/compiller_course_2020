
#ifndef MYCOMPILLER_CALLINSTRUCTION_H
#define MYCOMPILLER_CALLINSTRUCTION_H
#include <AsmInstruction.h>

class CallInstruction : public AsmInstruction {
 public:
  CallInstruction(const std::string&);
  void Print(std::ostream&) override;

 public:
  std::string func_;
};

#endif  // MYCOMPILLER_CALLINSTRUCTION_H

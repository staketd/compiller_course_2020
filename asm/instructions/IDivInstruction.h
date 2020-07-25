
#ifndef MYCOMPILLER_IDIVINSTRUCTION_H
#define MYCOMPILLER_IDIVINSTRUCTION_H

#include <AsmInstruction.h>

class IDivInstruction : public AsmInstruction {
 public:
  IDivInstruction(const std::string&);
  void Print(std::ostream&) override;

 public:
  std::string src_;
};

#endif  // MYCOMPILLER_IDIVINSTRUCTION_H

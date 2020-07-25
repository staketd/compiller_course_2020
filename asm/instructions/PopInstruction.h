
#ifndef MYCOMPILLER_POP_H
#define MYCOMPILLER_POP_H
#include <AsmInstruction.h>

class PopInstruction : public AsmInstruction {
 public:
  PopInstruction() = default;
  PopInstruction(const std::string&);
  void Print(std::ostream&) override;

 public:
  std::string reg_;
};

#endif  // MYCOMPILLER_POP_H

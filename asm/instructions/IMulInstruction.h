
#ifndef MYCOMPILLER_IMULINSTRUCTION_H
#define MYCOMPILLER_IMULINSTRUCTION_H
#include <AsmInstruction.h>

class IMulInstruction : public AsmInstruction {
 public:
  IMulInstruction(const std::string&, const std::string&);
  void Print(std::ostream&) override;

 public:
  std::string destination_;
  std::string source_;
};

#endif  // MYCOMPILLER_IMULINSTRUCTION_H

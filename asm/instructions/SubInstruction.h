
#ifndef MYCOMPILLER_SUBINSTRUCTION_H
#define MYCOMPILLER_SUBINSTRUCTION_H
#include <AsmInstruction.h>
class SubInstruction : public AsmInstruction {
 public:
  SubInstruction(const std::string&, const std::string&);
  void Print(std::ostream&) override;

 public:
  std::string destination_;
  std::string source_;
};

#endif  // MYCOMPILLER_SUBINSTRUCTION_H

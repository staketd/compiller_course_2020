
#ifndef MYCOMPILLER_ORINSTRUCTION_H
#define MYCOMPILLER_ORINSTRUCTION_H
#include <AsmInstruction.h>
class OrInstruction : public AsmInstruction {
 public:
  OrInstruction(const std::string&, const std::string&);
  void Print(std::ostream&) override;

 public:
  std::string destination_;
  std::string source_;
};

#endif  // MYCOMPILLER_ORINSTRUCTION_H

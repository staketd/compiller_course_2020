
#ifndef MYCOMPILLER_PUSHINSTRUCTION_H
#define MYCOMPILLER_PUSHINSTRUCTION_H
#include <AsmInstruction.h>

class PushInstruction : public AsmInstruction {
 public:
  PushInstruction(const std::string&);
  void Print(std::ostream&) override;

  std::vector<std::string> GetDef() override;
  std::vector<std::string> GetUse() override;
  void ChangeNames(
      ElementSetk* support,
      const std::vector<std::string>& change) override;

 public:
  std::string reg_;
};

#endif  // MYCOMPILLER_PUSHINSTRUCTION_H

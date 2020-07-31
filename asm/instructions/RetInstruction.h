
#ifndef MYCOMPILLER_RETINSTRUCTION_H
#define MYCOMPILLER_RETINSTRUCTION_H
#include <AsmInstruction.h>
class RetInstruction : public AsmInstruction {
 public:
  RetInstruction();
  void Print(std::ostream&) override;

  std::vector<std::string> GetDef() override;
  std::vector<std::string> GetUse() override;
  void ChangeNames(
      ElementSetk* support,
      const std::vector<std::string>& change) override;
};

#endif  // MYCOMPILLER_RETINSTRUCTION_H

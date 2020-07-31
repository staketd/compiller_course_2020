
#ifndef MYCOMPILLER_POP_H
#define MYCOMPILLER_POP_H
#include <AsmInstruction.h>

class PopInstruction : public AsmInstruction {
 public:
  PopInstruction();
  PopInstruction(const std::string&);
  void Print(std::ostream&) override;

  std::vector<std::string> GetDef() override;
  std::vector<std::string> GetUse() override;
  void ChangeNames(
      ElementSetk* support,
      const std::vector<std::string>& change) override;

 public:
  std::string reg_;
};

#endif  // MYCOMPILLER_POP_H

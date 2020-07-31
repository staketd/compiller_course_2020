
#ifndef MYCOMPILLER_IMULINSTRUCTION_H
#define MYCOMPILLER_IMULINSTRUCTION_H
#include <AsmInstruction.h>

class IMulInstruction : public AsmInstruction {
 public:
  IMulInstruction(const std::string&, const std::string&);
  void Print(std::ostream&) override;

  std::vector<std::string> GetDef() override;
  std::vector<std::string> GetUse() override;
  void ChangeNames(
      ElementSetk* support,
      const std::vector<std::string>& change) override;

 public:
  std::string destination_;
  std::string source_;
};

#endif  // MYCOMPILLER_IMULINSTRUCTION_H

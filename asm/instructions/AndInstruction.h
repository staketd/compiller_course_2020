
#ifndef MYCOMPILLER_ANDINSTRUCTION_H
#define MYCOMPILLER_ANDINSTRUCTION_H
#include <AsmInstruction.h>

class AndInstruction : public AsmInstruction {
 public:
  AndInstruction(const std::string&, const std::string&);
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

#endif  // MYCOMPILLER_ANDINSTRUCTION_H

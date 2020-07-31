
#ifndef MYCOMPILLER_ADDINSTRUCTION_H
#define MYCOMPILLER_ADDINSTRUCTION_H
#include <AsmInstruction.h>
class AddInstruction : public AsmInstruction {
 public:
  AddInstruction(const std::string&, const std::string&);
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

#endif  // MYCOMPILLER_ADDINSTRUCTION_H

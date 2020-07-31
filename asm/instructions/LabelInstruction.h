
#ifndef MYCOMPILLER_LABELINSTRUCTION_H
#define MYCOMPILLER_LABELINSTRUCTION_H
#include <AsmInstruction.h>
class LabelInstruction : public AsmInstruction {
 public:
  LabelInstruction(const std::string&);
  void Print(std::ostream&) override;

  std::vector<std::string> GetDef() override;
  std::vector<std::string> GetUse() override;

  void ChangeNames(
      ElementSetk* support,
      const std::vector<std::string>& change) override;

 public:
  std::string label_;
};

#endif  // MYCOMPILLER_LABELINSTRUCTION_H

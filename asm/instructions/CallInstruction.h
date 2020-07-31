
#ifndef MYCOMPILLER_CALLINSTRUCTION_H
#define MYCOMPILLER_CALLINSTRUCTION_H
#include <AsmInstruction.h>

class CallInstruction : public AsmInstruction {
 public:
  CallInstruction(const std::string&);
  void Print(std::ostream&) override;
  std::vector<std::string> GetDef() override;
  std::vector<std::string> GetUse() override;
  void ChangeNames(
      ElementSetk* support,
      const std::vector<std::string>& change) override;

 public:
  std::string func_;
};

#endif  // MYCOMPILLER_CALLINSTRUCTION_H

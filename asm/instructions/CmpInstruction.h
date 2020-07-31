
#ifndef MYCOMPILLER_CMPINSTRUCTION_H
#define MYCOMPILLER_CMPINSTRUCTION_H
#include <AsmInstruction.h>
class CmpInstruction : public AsmInstruction {
 public:
  CmpInstruction(const std::string&, const std::string&);
  void Print(std::ostream&) override;
  std::vector<std::string> GetDef() override;
  std::vector<std::string> GetUse() override;
  void ChangeNames(
      ElementSetk* support,
      const std::vector<std::string>& change) override;

 public:
  std::string left_;
  std::string right_;
};

#endif  // MYCOMPILLER_CMPINSTRUCTION_H


#ifndef MYCOMPILLER_WRITESYSCALL_H
#define MYCOMPILLER_WRITESYSCALL_H
#include <AsmInstruction.h>

class WriteSyscall : public AsmInstruction {
 public:
  WriteSyscall(const std::string&);
  void Print(std::ostream&) override;
  std::vector<std::string> GetUse() override;
  std::vector<std::string> GetDef() override;
  void ChangeNames(ElementSetk*, const std::vector<std::string>&) override;

 public:
  std::string src_;
};

#endif  // MYCOMPILLER_WRITESYSCALL_H


#ifndef MYCOMPILLER_EXITSYSCALL_H
#define MYCOMPILLER_EXITSYSCALL_H
#include <AsmInstruction.h>
class ExitSysCall : public AsmInstruction {
 public:
  ExitSysCall(size_t);
  void Print(std::ostream&) override;
  std::vector<std::string> GetDef() override;
  std::vector<std::string> GetUse() override;
  void ChangeNames(
      ElementSetk* support,
      const std::vector<std::string>& change) override;

 public:
  size_t exit_code_;
};

#endif  // MYCOMPILLER_EXITSYSCALL_H

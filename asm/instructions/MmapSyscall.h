
#ifndef MYCOMPILLER_MMAPSYSCALL_H
#define MYCOMPILLER_MMAPSYSCALL_H
#include <AsmInstruction.h>
class MmapSyscall : public AsmInstruction {
 public:
  MmapSyscall(size_t);
  void Print(std::ostream&) override;
  std::vector<std::string> GetUse() override;
  std::vector<std::string> GetDef() override;
  void ChangeNames(ElementSetk*, const std::vector<std::string>&) override;

 public:
  size_t size_;
};

#endif  // MYCOMPILLER_MMAPSYSCALL_H

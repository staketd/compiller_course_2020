
#ifndef MYCOMPILLER_JUMPINSTRUCTION_H
#define MYCOMPILLER_JUMPINSTRUCTION_H
#include <AsmInstruction.h>

enum class JumpType : char {
  jz,
  jnz,
  jne,
  jg,
  jl,
  jge,
  jle,
  jmp
};

class JumpInstruction : public AsmInstruction {
 public:
  JumpInstruction(const std::string&, JumpType);
  void Print(std::ostream&) override;

  std::vector<std::string> GetDef() override;
  std::vector<std::string> GetUse() override;
  void ChangeNames(
      ElementSetk* support,
      const std::vector<std::string>& change) override;

 public:
  std::string label_;
  JumpType jump_type_;
};

#endif  // MYCOMPILLER_JUMPINSTRUCTION_H

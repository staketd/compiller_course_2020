
#ifndef MYCOMPILLER_ASMINSTRUCTION_H
#define MYCOMPILLER_ASMINSTRUCTION_H
#include <string>
#include <Print.h>
#include <fstream>
#include <vector>
#include <ElementSet.h>

enum class AsmType {
  Add,
  And,
  Call,
  Cmp,
  Idiv,
  Imul,
  Jump,
  Label,
  Or,
  Mov,
  Pop,
  Ret,
  Sub,
  Push,
  Mmap,
  Write,
  Exit
};

class AsmInstruction {
 public:
  AsmInstruction(AsmType);
  virtual void Print(std::ostream&) = 0;
  virtual ~AsmInstruction() = default;
  virtual std::vector<std::string> GetDef() = 0;
  virtual std::vector<std::string> GetUse() = 0;
  virtual void ChangeNames(ElementSetk*, const std::vector<std::string>&) = 0;

  virtual AsmType Type();

 private:
  AsmType type_;
};

inline void ChangeRegName(std::string& name) {
  if (name == "::fp") {
    name = "rbp";
  }
  if (name == "::return_value") {
    name = "rax";
  }
}

inline void ChangeRegToPhysical(
    std::string& name,
    ElementSetk* support,
    const std::vector<std::string> change) {
  name = change[support->GetIndex(name)];
}

inline bool CheckConst(const std::string& name) {
  return name[0] >= '0' && name[0] <= '9';
}

#endif  // MYCOMPILLER_ASMINSTRUCTION_H


#include "IDivInstruction.h"
IDivInstruction::IDivInstruction(const std::string& src)
    : AsmInstruction(AsmType::Idiv), src_(src) {
}

void IDivInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tidiv ", src_, "\n");
}

std::vector<std::string> IDivInstruction::GetDef() {
  return {"rax", "rdx"};
}

std::vector<std::string> IDivInstruction::GetUse() {
  if (CheckConst(src_)) {
    return {"rax", "rdx"};
  }
  return {"rax", "rdx", src_};
}

void IDivInstruction::ChangeNames(ElementSetk* support,
                                  const std::vector<std::string>& change) {
  if (!CheckConst(src_)) {
    ChangeRegToPhysical(src_, support, change);
  }
}

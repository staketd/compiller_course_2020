
#include "PushInstruction.h"
PushInstruction::PushInstruction(const std::string& reg)
    : AsmInstruction(AsmType::Push), reg_(reg) {
}

void PushInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tpush ", reg_, "\n");
}

std::vector<std::string> PushInstruction::GetDef() {
  return std::vector<std::string>();
}

std::vector<std::string> PushInstruction::GetUse() {
  return {reg_};
}

void PushInstruction::ChangeNames(ElementSetk* support,
                                  const std::vector<std::string>& change) {
  ChangeRegToPhysical(reg_, support, change);
}

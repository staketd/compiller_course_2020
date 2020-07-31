
#include "PopInstruction.h"
PopInstruction::PopInstruction(const std::string& reg)
    : AsmInstruction(AsmType::Pop), reg_(reg) {
}

void PopInstruction::Print(std::ostream& ostream) {
  std::string space = " ";
  if (reg_.length() == 0) {
    space = "";
  }
  MyPrint(ostream, "\tpop", space, reg_, "\n");
}

std::vector<std::string> PopInstruction::GetDef() {
  if (reg_.length()) {
    return {reg_};
  }
  return {};
}

std::vector<std::string> PopInstruction::GetUse() {
  return {};
}

PopInstruction::PopInstruction() : AsmInstruction(AsmType::Pop) {
}

void PopInstruction::ChangeNames(ElementSetk* support,
                                 const std::vector<std::string>& change) {
  if (reg_.length()) {
    ChangeRegToPhysical(reg_, support, change);
  }
}

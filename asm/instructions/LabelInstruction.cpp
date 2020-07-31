
#include "LabelInstruction.h"

LabelInstruction::LabelInstruction(const std::string& label)
    : AsmInstruction(AsmType::Label), label_(label) {
}
void LabelInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, label_, ":\n");
}

std::vector<std::string> LabelInstruction::GetDef() {
  return {};
}

std::vector<std::string> LabelInstruction::GetUse() {
  return {};
}
void LabelInstruction::ChangeNames(ElementSetk* support,
                                   const std::vector<std::string>& change) {
}

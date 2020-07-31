
#include "RetInstruction.h"

void RetInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tret\n");
}

std::vector<std::string> RetInstruction::GetDef() {
  return std::vector<std::string>();
}
std::vector<std::string> RetInstruction::GetUse() {
  return {};
}

RetInstruction::RetInstruction() : AsmInstruction(AsmType::Ret) {
}
void RetInstruction::ChangeNames(ElementSetk* support,
                                 const std::vector<std::string>& change) {
}

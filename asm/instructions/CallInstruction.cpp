
#include "CallInstruction.h"

CallInstruction::CallInstruction(const std::string& func)
    : AsmInstruction(AsmType::Call), func_(func) {
}

void CallInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tcall ", func_, "\n");
}

std::vector<std::string> CallInstruction::GetDef() {
  return {"rax"};
}

std::vector<std::string> CallInstruction::GetUse() {
  return {};
}

void CallInstruction::ChangeNames(ElementSetk* support,
                                  const std::vector<std::string>& change) {
}

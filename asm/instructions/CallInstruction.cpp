
#include "CallInstruction.h"

CallInstruction::CallInstruction(const std::string& func)
    : AsmInstruction(AsmType::Call), func_(func) {
}

void CallInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tpush rcx\n");
  MyPrint(ostream, "\tpush rdx\n");
  MyPrint(ostream, "\tcall ", func_, "\n");
  MyPrint(ostream, "\tpop rdx\n");
  MyPrint(ostream, "\tpop rcx\n");
}

std::vector<std::string> CallInstruction::GetDef() {
  return {"rax", "rcx", "rdx"};
}

std::vector<std::string> CallInstruction::GetUse() {
  return {};
}

void CallInstruction::ChangeNames(ElementSetk* support,
                                  const std::vector<std::string>& change) {
}

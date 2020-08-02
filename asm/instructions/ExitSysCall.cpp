
#include "ExitSysCall.h"
ExitSysCall::ExitSysCall(size_t code)
    : AsmInstruction(AsmType::Exit), exit_code_(code) {
}

void ExitSysCall::Print(std::ostream& stream) {
  MyPrint(stream, "\tmov rax, 60\n");
  MyPrint(stream, "\tmov rdi, ", exit_code_, "\n");
  MyPrint(stream, "\tsyscall\n");
}
std::vector<std::string> ExitSysCall::GetDef() {
  return {"rax", "rdi"};
}
std::vector<std::string> ExitSysCall::GetUse() {
  return {};
}
void ExitSysCall::ChangeNames(ElementSetk* support,
                              const std::vector<std::string>& change) {
}

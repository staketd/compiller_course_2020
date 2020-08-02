
#include "WriteSyscall.h"
WriteSyscall::WriteSyscall(const std::string& src)
    : AsmInstruction(AsmType::Write), src_(src) {
}

void WriteSyscall::Print(std::ostream& stream) {
  MyPrint(stream, "\tpush rdi\n");
  MyPrint(stream, "\tpush rsi\n");
  MyPrint(stream, "\tpush rdx\n");
  MyPrint(stream, "\tpush ", src_, "\n");
  MyPrint(stream, "\tmov rdi, 1\n");
  MyPrint(stream, "\tmov rsi, rsp\n");
  MyPrint(stream, "\tmov rdx, 8\n");
  MyPrint(stream, "\tmov rax, 1\n");
  MyPrint(stream, "\tsyscall\n");
  MyPrint(stream, "\tpop ", src_, "\n");
  MyPrint(stream, "\tpop rdx\n");
  MyPrint(stream, "\tpop rsi\n");
  MyPrint(stream, "\tpop rdi\n");
}

std::vector<std::string> WriteSyscall::GetUse() {
  return {src_};
}

std::vector<std::string> WriteSyscall::GetDef() {
  return {"rax"};
}
void WriteSyscall::ChangeNames(ElementSetk* support,
                               const std::vector<std::string>& change) {
  ChangeRegToPhysical(src_, support, change);
}

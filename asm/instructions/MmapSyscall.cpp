
#include "MmapSyscall.h"
MmapSyscall::MmapSyscall(size_t size)
    : AsmInstruction(AsmType::Mmap), size_(size) {
}

void MmapSyscall::Print(std::ostream& stream) {
  MyPrint(stream, "\tpush rdi\n");
  MyPrint(stream, "\tpush rsi\n");
  MyPrint(stream, "\tpush rdx\n");
  MyPrint(stream, "\tpush r10\n");
  MyPrint(stream, "\tpush r8\n");
  MyPrint(stream, "\tpush r9\n");
  MyPrint(stream, "\tpush rdx\n");
  MyPrint(stream, "\tpush rcx\n");
  MyPrint(stream, "\tmov rdi, 0\n");
  MyPrint(stream, "\tmov rsi, ", size_, "\n");
  MyPrint(stream, "\tmov rdx, 3\n");
  MyPrint(stream, "\tmov r10, 0x22\n");
  MyPrint(stream, "\tmov r8, -1\n");
  MyPrint(stream, "\tmov r9, 0\n");
  MyPrint(stream, "\tmov rax, 0x9\n");
  MyPrint(stream, "\tsyscall\n");
  MyPrint(stream, "\tpop rcx\n");
  MyPrint(stream, "\tpop rdx\n");
  MyPrint(stream, "\tpop r9\n");
  MyPrint(stream, "\tpop r8\n");
  MyPrint(stream, "\tpop r10\n");
  MyPrint(stream, "\tpop rdx\n");
  MyPrint(stream, "\tpop rsi\n");
  MyPrint(stream, "\tpop rdi\n");
}

std::vector<std::string> MmapSyscall::GetUse() {
  return {};
}
std::vector<std::string> MmapSyscall::GetDef() {
  return {"rax"};
}

void MmapSyscall::ChangeNames(ElementSetk*, const std::vector<std::string>&) {
}


#include "JumpInstruction.h"
JumpInstruction::JumpInstruction(const std::string& label, JumpType type)
    : label_(label), type_(type) {
}

void JumpInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\t");
  switch (type_) {
    case JumpType::jz:
      MyPrint(ostream, "jz ");
      break;
    case JumpType::jnz:
      MyPrint(ostream, "jnz ");
      break;
    case JumpType::jne:
      MyPrint(ostream, "jne ");
      break;
    case JumpType::jg:
      MyPrint(ostream, "jg ");
      break;
    case JumpType::jl:
      MyPrint(ostream, "jl ");
      break;
    case JumpType::jge:
      MyPrint(ostream, "jge ");
      break;
    case JumpType::jle:
      MyPrint(ostream, "jle ");
      break;
    case JumpType::jmp:
      MyPrint(ostream, "jmp ");
  }
  MyPrint(ostream, label_, "\n");
}

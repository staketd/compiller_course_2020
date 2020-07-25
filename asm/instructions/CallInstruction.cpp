
#include "CallInstruction.h"

CallInstruction::CallInstruction(const std::string& func) : func_(func) {
}

void CallInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tcall ", func_, "\n");
}

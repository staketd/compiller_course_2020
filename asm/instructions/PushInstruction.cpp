
#include "PushInstruction.h"
PushInstruction::PushInstruction(const std::string& reg) : reg_(reg) {
}

void PushInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tpush ", reg_, "\n");
}

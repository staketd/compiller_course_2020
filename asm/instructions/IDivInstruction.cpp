
#include "IDivInstruction.h"
IDivInstruction::IDivInstruction(const std::string& src) : src_(src) {
}

void IDivInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tidiv ", src_, "\n");
}

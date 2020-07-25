
#include "PopInstruction.h"
PopInstruction::PopInstruction(const std::string& reg) : reg_(reg) {
}

void PopInstruction::Print(std::ostream& ostream) {
  std::string space = " ";
  if (reg_.length() == 0) {
    space = "";
  }
  MyPrint(ostream, "\tpop", space, reg_, "\n");
}

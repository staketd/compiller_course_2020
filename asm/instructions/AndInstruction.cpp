
#include "AndInstruction.h"
AndInstruction::AndInstruction(const std::string& dst, const std::string& src)
    : destination_(dst), source_(src) {
}

void AndInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tand ", destination_, ", ", source_, "\n");
}

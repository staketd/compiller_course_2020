
#include "SubInstruction.h"
SubInstruction::SubInstruction(const std::string& dst, const std::string& src)
    : destination_(dst), source_(src) {
}

void SubInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tsub ", destination_, ", ", source_, "\n");
}

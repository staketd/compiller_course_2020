
#include "IMulInstruction.h"

IMulInstruction::IMulInstruction(const std::string& dst, const std::string& src)
    : destination_(dst), source_(src) {
}

void IMulInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\timul ", destination_, ", ", source_, "\n");
}

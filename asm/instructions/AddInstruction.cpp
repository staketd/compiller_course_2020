
#include "AddInstruction.h"
AddInstruction::AddInstruction(const std::string& dest, const std::string& src)
    : destination_(dest), source_(src) {
}

void AddInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tadd ", destination_, ", ", source_, "\n");
}

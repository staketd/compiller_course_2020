
#include "OrInstruction.h"
OrInstruction::OrInstruction(const std::string& dst, const std::string& src)
    : destination_(dst), source_(src) {
}

void OrInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tor ", destination_, ", ", source_);
}

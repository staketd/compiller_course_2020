
#include "LabelInstruction.h"

LabelInstruction::LabelInstruction(const std::string& label) : label_(label) {
}
void LabelInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, label_, ":\n");
}

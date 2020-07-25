
#include "CmpInstruction.h"
CmpInstruction::CmpInstruction(const std::string& left,
                               const std::string& right)
    : left_(left), right_(right) {
}
void CmpInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tcmp ", left_, ", ", right_, "\n");
}

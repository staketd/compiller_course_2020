
#include "AsmInstruction.h"
AsmType AsmInstruction::Type() {
  return type_;
}
AsmInstruction::AsmInstruction(AsmType type) : type_(type) {
}

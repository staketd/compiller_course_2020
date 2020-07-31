
#include "AddInstruction.h"
AddInstruction::AddInstruction(const std::string& dest, const std::string& src)
    : AsmInstruction(AsmType::Add), destination_(dest), source_(src) {
}

void AddInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tadd ", destination_, ", ", source_, "\n");
}

std::vector<std::string> AddInstruction::GetDef() {
  return {destination_};
}

std::vector<std::string> AddInstruction::GetUse() {
  if (CheckConst(source_)) {
    return {};
  }
  return {destination_, source_};
}

void AddInstruction::ChangeNames(ElementSetk* support,
                                 const std::vector<std::string>& change) {
  ChangeRegToPhysical(destination_, support, change);
  if (!CheckConst(source_)) {
    ChangeRegToPhysical(source_, support, change);
  }
}

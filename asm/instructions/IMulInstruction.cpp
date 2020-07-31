
#include "IMulInstruction.h"

IMulInstruction::IMulInstruction(const std::string& dst, const std::string& src)
    :AsmInstruction(AsmType::Imul), destination_(dst), source_(src) {
}

void IMulInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\timul ", destination_, ", ", source_, "\n");
}

std::vector<std::string> IMulInstruction::GetDef() {
  return {destination_};
}

std::vector<std::string> IMulInstruction::GetUse() {
  if (CheckConst(source_)) {
    return {destination_};
  }
  return {destination_, source_};
}

void IMulInstruction::ChangeNames(ElementSetk* support,
                                  const std::vector<std::string>& change) {
  ChangeRegToPhysical(destination_, support, change);
  if (!CheckConst(source_)) {
    ChangeRegToPhysical(source_, support, change);
  }
}

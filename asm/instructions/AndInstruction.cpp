
#include "AndInstruction.h"
AndInstruction::AndInstruction(const std::string& dst, const std::string& src)
    :AsmInstruction(AsmType::And), destination_(dst), source_(src) {
}

void AndInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tand ", destination_, ", ", source_, "\n");
}

std::vector<std::string> AndInstruction::GetDef() {
  return {destination_};
}

std::vector<std::string> AndInstruction::GetUse() {
  if (CheckConst(source_)) {
    return {};
  }
  return {destination_, source_};
}

void AndInstruction::ChangeNames(ElementSetk* support,
                                 const std::vector<std::string>& change) {
  ChangeRegToPhysical(destination_, support, change);
  if (!CheckConst(source_)) {
    ChangeRegToPhysical(source_, support, change);
  }
}

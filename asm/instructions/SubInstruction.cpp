
#include "SubInstruction.h"
SubInstruction::SubInstruction(const std::string& dst, const std::string& src)
    : AsmInstruction(AsmType::Sub), destination_(dst), source_(src) {
}

void SubInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tsub ", destination_, ", ", source_, "\n");
}

std::vector<std::string> SubInstruction::GetDef() {
  return {destination_};
}
std::vector<std::string> SubInstruction::GetUse() {
  if (CheckConst(source_)) {
    return {destination_};
  }
  return {destination_, source_};
}
void SubInstruction::ChangeNames(ElementSetk* support,
                                 const std::vector<std::string>& change) {
  ChangeRegToPhysical(destination_, support, change);
  if (!CheckConst(source_)) {
    ChangeRegToPhysical(source_, support, change);
  }
}

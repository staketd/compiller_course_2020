
#include "OrInstruction.h"
OrInstruction::OrInstruction(const std::string& dst, const std::string& src)
    : AsmInstruction(AsmType::Or), destination_(dst), source_(src) {
}

void OrInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tor ", destination_, ", ", source_);
}

std::vector<std::string> OrInstruction::GetDef() {
  return {destination_};
}

std::vector<std::string> OrInstruction::GetUse() {
  if (CheckConst(source_)) {
    return {destination_};
  }
  return {destination_, source_};
}

void OrInstruction::ChangeNames(ElementSetk* support,
                                const std::vector<std::string>& change) {
  ChangeRegToPhysical(destination_, support, change);

  if (!CheckConst(source_)) {
    ChangeRegToPhysical(source_, support, change);
  }
}


#include "CmpInstruction.h"
CmpInstruction::CmpInstruction(const std::string& left,
                               const std::string& right)
    :AsmInstruction(AsmType::Cmp), left_(left), right_(right) {
}
void CmpInstruction::Print(std::ostream& ostream) {
  MyPrint(ostream, "\tcmp ", left_, ", ", right_, "\n");
}

std::vector<std::string> CmpInstruction::GetDef() {
  return {};
}

std::vector<std::string> CmpInstruction::GetUse() {
  std::vector<std::string> result;
  if (!CheckConst(left_)) {
    result.push_back(left_);
  }
  if (!CheckConst(right_)) {
    result.push_back(right_);
  }
  return result;
}

void CmpInstruction::ChangeNames(ElementSetk* support,
                                 const std::vector<std::string>& change) {
  if (!CheckConst(left_)) {
    ChangeRegToPhysical(left_, support, change);
  }

  if (!CheckConst(right_)) {
    ChangeRegToPhysical(right_, support, change);
  }
}

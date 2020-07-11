
#include "LogicOperatorType.h"

std::string ir_tree::ToString(LogicOperatorType type) {
  switch (type) {
    case LogicOperatorType::LE:
      return "LE";
    case LogicOperatorType::GE:
      return "GE";
    case LogicOperatorType::LT:
      return "LT";
    case LogicOperatorType::GT:
      return "LT";
    case LogicOperatorType::NE:
      return "NE";
    case LogicOperatorType::EQ:
      return "EQ";
    default:
      return "KEK";
  }
}


#include "BinOperatorType.h"

std::string ir_tree::ToString(BinOperatorType type) {
  switch (type) {
    case BinOperatorType::PLUS:
      return "PLUS";
    case BinOperatorType::MINUS:
      return "MINUS";
    case BinOperatorType::DIV:
      return "DIV";
    case BinOperatorType::MUL:
      return "MUL";
    case BinOperatorType::OR:
      return "OR";
    case BinOperatorType::AND:
      return "AND";
    default:
      return "KEK";
  }
}
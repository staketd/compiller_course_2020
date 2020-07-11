
#ifndef MYCOMPILLER_BINOPERATORTYPE_H
#define MYCOMPILLER_BINOPERATORTYPE_H

#include <string>

namespace ir_tree {

enum class BinOperatorType : char {
  PLUS,
  MINUS,
  MUL,
  DIV,
  AND,
  OR,
  MOD
};

std::string ToString(BinOperatorType type);

} // namespace ir_tree
#endif  // MYCOMPILLER_BINOPERATORTYPE_H

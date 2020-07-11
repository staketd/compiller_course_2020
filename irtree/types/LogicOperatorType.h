
#ifndef MYCOMPILLER_LOGICOPERATORTYPE_H
#define MYCOMPILLER_LOGICOPERATORTYPE_H

#include <string>

namespace ir_tree {

enum class LogicOperatorType {
  LT,
  GT,
  LE,
  GE,
  EQ,
  NE,
};

std::string ToString(LogicOperatorType type);

}
#endif  // MYCOMPILLER_LOGICOPERATORTYPE_H

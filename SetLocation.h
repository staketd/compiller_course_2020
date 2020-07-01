#pragma once

#include <BaseASTClass.h>

inline void SetLocation(BaseASTClass* node, yy::location loc) {
  node->loc = loc;
}

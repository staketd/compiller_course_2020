
#include "Integer.h"

int Integer::ToInt() {
    return value_;
}

Integer::Integer(int val) : PrimitiveObject("Integer"), value_(val) {
}

bool Integer::IsInteger() {
  return true;
}

Integer::Integer() : PrimitiveObject("Integer") {
  value_ = 0;
}


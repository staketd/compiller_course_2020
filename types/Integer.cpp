
#include "Integer.h"

int Integer::ToInt() {
    return value_;
}

Integer::Integer(int val) : value_(val) {
}

bool Integer::IsInteger() {
  return true;
}
Integer::Integer() {
  value_ = 0;
}

BaseType* Integer::GetType() {
  return new Integer();
}

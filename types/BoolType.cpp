
#include "BoolType.h"

bool BoolType::IsBool() {
  return true;
}

BoolType::BoolType(bool value) : value_(value){
}

int BoolType::ToInt() {
  return (int)value_;
}

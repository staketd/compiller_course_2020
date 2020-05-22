
#include "BoolObject.h"

bool BoolObject::IsBool() {
  return true;
}

BoolObject::BoolObject(bool value) : PrimitiveObject("Bool"), value_(value) {
}

int BoolObject::ToInt() {
  return (int)value_;
}

BoolObject::BoolObject() : PrimitiveObject("Bool"), value_(false) {
}

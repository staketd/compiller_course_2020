
#include "FunctionObject.h"
#include <stdexcept>
#include <utility>

FunctionObject::FunctionObject() : BaseObject("Function") {
}

int FunctionObject::ToInt() {
    throw std::runtime_error("Function cannot be assigned to variable");
}

bool FunctionObject::IsFunction() {
  return true;
}


#include "FunctionType.h"
#include <stdexcept>
#include <utility>

FunctionType::FunctionType() {
}

int FunctionType::ToInt() {
    throw std::runtime_error("Function cannot be assigned to variable");
}

bool FunctionType::IsFunction() {
  return true;
}
BaseType* FunctionType::GetType() {
  return new FunctionType();
}

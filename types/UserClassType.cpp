#include "UserClassType.h"
#include <stdexcept>

int UserClassType::ToInt() {
    throw std::runtime_error("Type cannot be assigned to variable");
}

bool UserClassType::IsUserClass() {
  return true;
}

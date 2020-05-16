#include "ClassType.h"
#include <stdexcept>

int ClassType::ToInt() {
    throw std::runtime_error("Type cannot be assigned to variable");
}

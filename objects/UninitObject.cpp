
#include "UninitObject.h"
#include <stdexcept>

int UninitObject::ToInt() {
    throw std::runtime_error("Variable is not initialized");
}

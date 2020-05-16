
#include "FunctionType.h"
#include <stdexcept>
#include <utility>

FunctionType::FunctionType(std::vector<std::string>  names) : arguments_names_(std::move(names)) {
}

int FunctionType::ToInt() {
    throw std::runtime_error("Function cannot be assigned to variable");
}

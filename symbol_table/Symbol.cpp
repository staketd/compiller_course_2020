
#include "Symbol.h"

Symbol::Symbol(std::string name) : name_(std::move(name)) {
}

std::string Symbol::GetName() const {
    return name_;
}

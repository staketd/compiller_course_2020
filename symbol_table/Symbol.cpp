
#include "Symbol.h"

Symbol::Symbol(std::string name) : name_(std::move(name)) {
}

std::string Symbol::GetName() const {
    return name_;
}

bool Symbol::operator==(const Symbol& other) const {
    return other.name_ == name_;
}

bool Symbol::operator!=(const Symbol& other) const {
    return !(other.name_ == name_);
}

Symbol::Symbol(const Symbol& other) : Symbol(other.name_) {
}

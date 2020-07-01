
#include "Temp.h"

ir_tree::Temp::Temp() : name_(std::to_string(counter++)) {
}

ir_tree::Temp::Temp(const std::string& name) : name_(name) {
}

std::string ir_tree::Temp::ToString() const {
  return name_;
}


#include "Label.h"

ir_tree::Label::Label() : label_("L" + std::to_string(counter)) {
  counter++;
}

ir_tree::Label::Label(const std::string& name) : label_(name) {
}

std::string ir_tree::Label::ToString() const {
  return label_;
}

size_t ir_tree::Label::counter = 0;

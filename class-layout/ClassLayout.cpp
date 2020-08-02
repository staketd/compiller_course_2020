
#include "ClassLayout.h"
void ClassLayout::AddField(const Symbol& field) {
  offsets_[field] = current_offset_;
  current_offset_ += 8;
  class_size_ += 8;
}

size_t ClassLayout::GetOffset(const Symbol& field) {
  return offsets_[field];
}

bool ClassLayout::HasField(const Symbol& symbol) const {
  return offsets_.find(symbol) != offsets_.end();
}

std::string ClassLayout::GetName() const {
  return class_name_;
}
ClassLayout::ClassLayout(const std::string& name) : class_name_(name) {
}

size_t ClassLayout::GetSize() {
  return class_size_;
}

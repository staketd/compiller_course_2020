
#include "ArrayObject.h"

ArrayObject::ArrayObject(std::string name, size_t size,
                         const std::vector<std::shared_ptr<BaseObject>>& array)
    : BaseObject("Array"), name_(name), size_(size), array_(array) {
}
int ArrayObject::ToInt() {
  throw std::runtime_error("Array cannot be converted to Int");
}

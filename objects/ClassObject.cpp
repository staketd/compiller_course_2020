#include "ClassObject.h"
#include <stdexcept>

int ClassObject::ToInt() {
  throw std::runtime_error("Type cannot be assigned to variable");
}

bool ClassObject::IsUserClass() {
  return true;
}

ClassObject::ClassObject(const std::string& name) : BaseObject(name) {
}

std::shared_ptr<BaseObject> ClassObject::GetValue(const Symbol& symbol) {
  if (fields_.find(symbol) == fields_.end()) {
    throw std::runtime_error("Variable \"" + symbol.GetName() +
                             "\" was not declared");
  }
  return fields_[symbol];
}

void ClassObject::SetValue(const Symbol& symbol,
                           std::shared_ptr<BaseObject> obj) {
  if (fields_.find(symbol) == fields_.end()) {
    throw std::runtime_error("Variable \"" + symbol.GetName() +
                             "\" was not declared");
  }
  fields_[symbol] = obj;
}

void ClassObject::CreateField(const Symbol& symbol,
                              std::shared_ptr<BaseObject> init) {
  fields_[symbol] = init;
}


#include "ClassMap.h"

void ClassMap::SetClass(const Symbol& symbol, Class* cl) {
  classes_[symbol] = cl;
}

Class* ClassMap::GetClass(const Symbol& symbol) {
  if (classes_.find(symbol) == classes_.end()) {
    throw std::runtime_error("No such class");
  }
  return classes_[symbol];
}

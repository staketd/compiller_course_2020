
#include "FunctionMap.h"
void FunctionMap::Set(const Symbol& symb, Function* function) {
  functions_[symb] = function;
}

Function* FunctionMap::Get(const Symbol& symb) {
  return functions_[symb];
}

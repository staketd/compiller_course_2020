
#include "FunctionMap.h"
void FunctionMap::Set(const Symbol& symb, ClassMethod* function) {
  functions_[symb] = function;
}

ClassMethod* FunctionMap::Get(const Symbol& symb) {
  return functions_[symb];
}

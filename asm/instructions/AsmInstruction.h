
#ifndef MYCOMPILLER_ASMINSTRUCTION_H
#define MYCOMPILLER_ASMINSTRUCTION_H
#include <string>
#include <Print.h>
#include <fstream>

class AsmInstruction {
 public:
  virtual void Print(std::ostream&) = 0;
  virtual ~AsmInstruction() = default;
};

inline void ChangeRegName(std::string& name) {
  if (name == "::fp") {
    name = "rbp";
  }
  if (name == "::return_value") {
    name = "rax";
  }
}

#endif  // MYCOMPILLER_ASMINSTRUCTION_H


#ifndef MYCOMPILLER_LABELINSTRUCTION_H
#define MYCOMPILLER_LABELINSTRUCTION_H
#include <AsmInstruction.h>
class LabelInstruction : public AsmInstruction {
 public:
  LabelInstruction(const std::string&);
  void Print(std::ostream&) override;

 public:
  std::string label_;
};

#endif  // MYCOMPILLER_LABELINSTRUCTION_H

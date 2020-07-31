
#ifndef MYCOMPILLER_MOVINSTRUCTION_H
#define MYCOMPILLER_MOVINSTRUCTION_H

#include <AsmInstruction.h>

class MovInstruction : public AsmInstruction {
 public:
  MovInstruction(const std::string&, const std::string&, int = 0, int = 0,
                 bool = false, bool = false);
  void Print(std::ostream&) override;

  std::vector<std::string> GetDef() override;
  std::vector<std::string> GetUse() override;
  void ChangeNames(
      ElementSetk* support,
      const std::vector<std::string>& change) override;

 public:
  std::string destination_;
  std::string source_;
  int dst_offset_;
  int src_offset_;
  bool dst_mem_;
  bool src_mem_;
};

#endif  // MYCOMPILLER_MOVINSTRUCTION_H

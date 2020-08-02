
#ifndef MYCOMPILLER_ASMGENERATOR_H
#define MYCOMPILLER_ASMGENERATOR_H

#include <TemplateBaseVisitor.h>
#include <Temp.h>
#include <fstream>
#include <IRExpression.h>
#include <BinOperatorType.h>
#include <AsmInstruction.h>
#include <vector>

const std::vector<std::string> x86_regs = {
    "rax", "rdx", "rcx", "rsi", "rdi", "rbx", "r8",  "r9",
    "r10", "r11", "r12", "r13", "r14", "r15", "rbp", "rsp"};

namespace ir_tree {
class AsmGenerator : public ir_tree::TemplateBaseVisitor<std::string> {
 public:
  AsmGenerator(const std::string&);
  void AddEpilogue();
  void AddPrologue();
  void AddExit(size_t);
  void PrintAll(std::ostream&);
  void SetStackOffset(size_t);
  std::vector<AsmInstruction*>& GetInstructions();

 private:
  void Visit(BinOpExpression*) override;
  void Visit(CallExpression*) override;
  void Visit(ConstExpression*) override;
  void Visit(EseqExpression*) override;
  void Visit(MemExpression*) override;
  void Visit(NameExpression*) override;
  void Visit(TempExpression*) override;
  void Visit(ExpStatement*) override;
  void Visit(JumpStatement*) override;
  void Visit(JumpConditionalStatement*) override;
  void Visit(LabelStatement*) override;
  void Visit(MoveStatement*) override;
  void Visit(SeqStatement*) override;
  void Visit(ExpressionList*) override;
  void Visit(IRPrintStatement*) override;
  void Visit(AllocExpression*) override;

  std::string BinOp(IRExpression*, IRExpression*, BinOperatorType);

  std::string Div(IRExpression*, IRExpression*, BinOperatorType);
  void PrintInstructions(std::ostream&);
  void PrintHead(std::ostream&);

 private:
  void Add(AsmInstruction*);
  std::vector<AsmInstruction*> instructions_;
  size_t stack_offset_;
};
}  // namespace ir_tree
#endif  // MYCOMPILLER_ASMGENERATOR_H

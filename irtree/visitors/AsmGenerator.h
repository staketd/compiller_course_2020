
#ifndef MYCOMPILLER_ASMGENERATOR_H
#define MYCOMPILLER_ASMGENERATOR_H

#include <TemplateBaseVisitor.h>
#include <Temp.h>
#include <fstream>
#include <IRExpression.h>
#include <BinOperatorType.h>
#include <AsmInstruction.h>
#include <vector>

namespace ir_tree {
class AsmGenerator : public ir_tree::TemplateBaseVisitor<std::string> {
 public:
  AsmGenerator(const std::string&, const std::string&);
  void PrintEpilogue();
  void PrintPrologue();
  void PrintAll();

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

  std::string BinOp(IRExpression*, IRExpression*, BinOperatorType);

  std::string Div(IRExpression*, IRExpression*, BinOperatorType);
  void PrintInstructions();
  void PrintHead();

 private:
  void Add(AsmInstruction*);
  std::vector<AsmInstruction*> instructions_;
  std::ofstream stream_;
};
}  // namespace ir_tree
#endif  // MYCOMPILLER_ASMGENERATOR_H


#ifndef MYCOMPILLER_IRPRINTVISITOR_H
#define MYCOMPILLER_IRPRINTVISITOR_H
#include <BaseVisitors.h>
#include <iostream>
#include <fstream>

namespace ir_tree {
class IRPrintVisitor : public ir_tree::BaseIRVisitor {
 public:
  IRPrintVisitor(std::ofstream&);
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

  void PrintTabs();
  std::ofstream& stream_;
  size_t tabs_;
};
}  // namespace ir_tree

#endif  // MYCOMPILLER_IRPRINTVISITOR_H

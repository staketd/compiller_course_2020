
#ifndef MYCOMPILLER_ELIMINATEDOUBLECALLS_H
#define MYCOMPILLER_ELIMINATEDOUBLECALLS_H
#include <TemplateBaseVisitor.h>
#include <IRUnion.h>
#include <SubtreeWrapper.h>
namespace ir_tree {
class EliminateDoubleCalls : public ir_tree::TemplateBaseVisitor<IRUnion> {
 public:
  EliminateDoubleCalls() = default;
  ir_tree::SubtreeWrapper* GetTree();
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
};
}
#endif  // MYCOMPILLER_ELIMINATEDOUBLECALLS_H

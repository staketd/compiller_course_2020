
#ifndef MYCOMPILLER_ELIMINATEESEQ_H
#define MYCOMPILLER_ELIMINATEESEQ_H
#include <TemplateBaseVisitor.h>
#include <IRUnion.h>
namespace ir_tree {
class EliminateEseq : public ir_tree::TemplateBaseVisitor<IRUnion> {
 public:
  ir_tree::IRStatement* GetTree();
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
};
}  // namespace ir_tree

#endif  // MYCOMPILLER_ELIMINATEESEQ_H

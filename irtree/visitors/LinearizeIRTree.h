
#ifndef MYCOMPILLER_LINEARIZEIRTREE_H
#define MYCOMPILLER_LINEARIZEIRTREE_H
#include <TemplateBaseVisitor.h>
#include <IRUnion.h>
#include <vector>

namespace ir_tree {
class LinearizeIRTree : public ir_tree::TemplateBaseVisitor<IRUnion> {
 public:
  IRStatement* GetTree();
  std::vector<IRStatement*> GetStatementList();
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
}
#endif  // MYCOMPILLER_LINEARIZEIRTREE_H

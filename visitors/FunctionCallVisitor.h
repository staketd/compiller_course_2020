
#ifndef MYCOMPILLER_FUNCTIONCALLVISITOR_H
#define MYCOMPILLER_FUNCTIONCALLVISITOR_H
#include <TemplateBaseVisitor.h>
#include <ScopeLayer.h>
#include <vector>
#include <Frame.h>
#include <FunctionTable.h>
#include <ScopeLayerTree.h>
#include <FunctionMap.h>

class FunctionCallVisitor : public TemplateBaseVisitor<int> {
 public:
  FunctionCallVisitor(Frame, FunctionMap&, ScopeLayerTree&, ScopeLayer*);
  void ExecuteCode(Function*);

 private:
  void Visit(StatementList*) override;
  void Visit(Assignment*) override;
  void Visit(AddExpression*) override;
  void Visit(MulExpression*) override;
  void Visit(DivExpression*) override;
  void Visit(SubstractExpression*) override;
  void Visit(IdentExpression*) override;
  void Visit(NumExpression*) override;
  void Visit(Program*) override;
  void Visit(PrintStatement*) override;
  void Visit(ReadStatement*) override;
  void Visit(EqualExpression*) override;
  void Visit(LessExpression*) override;
  void Visit(GreaterExpression*) override;
  void Visit(LessOrEqualExpression*) override;
  void Visit(GreaterOrEqualExpression*) override;
  void Visit(IfStatement*) override;
  void Visit(Scope*) override;
  void Visit(VariableDeclaration*) override;
  void Visit(ModuloExpression*) override;
  void Visit(WhileStatement*) override;
  void Visit(CallArgumentList*) override;
  void Visit(Function*) override;
  void Visit(FuncArgumentList*) override;
  void Visit(FunctionList*) override;
  void Visit(FuncCallExpression*) override;
  void Visit(ReturnStatement*) override;
  void Visit(FuncCallStatement*) override;

 private:
  int GetValue(const Symbol&);
  void SetValue(const Symbol&, int);

 private:
  FunctionTable table_;
  FunctionMap& functions_;
  ScopeLayerTree& tree_;
  Frame frame_;
  ScopeLayer* current_layer_;
  std::vector<int> current_children_;
  bool returned_{false};
};

#endif  // MYCOMPILLER_FUNCTIONCALLVISITOR_H

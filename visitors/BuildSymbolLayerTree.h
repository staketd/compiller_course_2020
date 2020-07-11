
#ifndef MYCOMPILLER_BUILDSYMBOLLAYERTREE_H
#define MYCOMPILLER_BUILDSYMBOLLAYERTREE_H
#include <BaseVisitors.h>
#include <ScopeLayer.h>
#include <ScopeLayerTree.h>
#include <FunctionMap.h>
#include <ClassMap.h>

class BuildSymbolLayerTree : public BaseASTVisitor {
 public:
  BuildSymbolLayerTree(ScopeLayerTree&, FunctionMap&, ClassMap&);
  void BuildTree(Program*);

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
  void Visit(ClassMethod*) override;
  void Visit(MethodArgumentList*) override;
  void Visit(ClassBody*) override;
  void Visit(MethodCallExpression*) override;
  void Visit(ReturnStatement*) override;
  void Visit(MethodCallStmt*) override;
  void Visit(Class*) override;
  void Visit(ClassList*) override;
  void Visit(ClassField*) override;
  void Visit(ClassMain*) override;
  void Visit(ThisExpression*) override;
  void Visit(NewExpression*) override;
  void Visit(ArrayDeclaration*) override;
  void Visit(ArrayAssignment*) override;
  void Visit(ArrayExpression*) override;
  void Visit(LogicAndExpression*) override;
  void Visit(LogicOrExpression*) override;

  bool IsCorrectVariableType(const std::string& type);

 private:
  std::string current_class_name_;
  ClassMap& class_map_;
  ScopeLayerTree& tree_;
  ScopeLayer* current_layer_;
  FunctionMap& functions_;
};

#endif  // MYCOMPILLER_BUILDSYMBOLLAYERTREE_H

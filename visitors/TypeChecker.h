
#ifndef MYCOMPILLER_VISITORS_TYPECHECKER_H_
#define MYCOMPILLER_VISITORS_TYPECHECKER_H_
#include <BaseVisitor.h>
#include <ScopeLayerTree.h>
#include <FunctionMap.h>
#include <TemplateBaseVisitor.h>

class TypeChecker : public TemplateBaseVisitor<std::shared_ptr<BaseType>> {
 public:
  TypeChecker(ScopeLayer*, FunctionMap&, ScopeLayerTree&);
  void CheckType(Program*);

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
  void Visit(ClassMethod*) override;
  void Visit(ClassBody*) override;
  void Visit(MethodArgumentList*) override;
  void Visit(CallArgumentList*) override;
  void Visit(MethodCallExpression*) override;
  void Visit(ReturnStatement*) override;
  void Visit(MethodCallStmt*) override;
  void Visit(Class*) override;
  void Visit(ClassList*) override;
  void Visit(ClassField*) override;
  void Visit(ClassMain*) override;
  void Visit(ThisExpression*) override;
  void Visit(NewExpression*) override;

  void CheckIntegerOperation(BinaryExpression*);

 private:
  Class* current_class_;
  ClassMethod* current_method_;
  FunctionMap& func_map_;
  ScopeLayer* current_layer_;
  ScopeLayerTree& tree_;
  std::vector<size_t> current_children_;
};

#endif  // MYCOMPILLER_VISITORS_TYPECHECKER_H_


#ifndef MYCOMPILLER_VISITORS_TYPECHECKER_H_
#define MYCOMPILLER_VISITORS_TYPECHECKER_H_
#include <BaseVisitor.h>
#include <ScopeLayer.h>
#include <FunctionMap.h>

class TypeChecker : public BaseVisitor {
 public:
  TypeChecker(ScopeLayer*, FunctionMap&);
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
  void Visit(Function*) override;
  void Visit(FunctionList*) override;
  void Visit(FuncArgumentList*) override;
  void Visit(CallArgumentList*) override;
  void Visit(FuncCallExpression*) override;
  void Visit(ReturnStatement*) override;
  void Visit(FuncCallStatement*) override;

 private:
  FunctionMap& func_map_;
  ScopeLayer* current_layer_;
  std::vector<size_t> current_children_;
};

#endif  // MYCOMPILLER_VISITORS_TYPECHECKER_H_

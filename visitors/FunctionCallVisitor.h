
#ifndef MYCOMPILLER_FUNCTIONCALLVISITOR_H
#define MYCOMPILLER_FUNCTIONCALLVISITOR_H
#include <TemplateBaseVisitor.h>
#include <ScopeLayer.h>
#include <vector>
#include <Frame.h>
#include <CallTable.h>
#include <ScopeLayerTree.h>
#include <FunctionMap.h>
#include <ClassMap.h>

class FunctionCallVisitor
    : public TemplateBaseVisitor<std::shared_ptr<BaseObject>> {
 public:
  FunctionCallVisitor(Frame, FunctionMap&, ScopeLayerTree&, ScopeLayer*,
                      std::shared_ptr<ClassObject>, ClassMap&);
  void ExecuteCode(ClassMethod*);

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

  std::shared_ptr<ClassObject> InitClass(Class*);

 private:
  std::shared_ptr<BaseObject> GetValue(const Symbol&);
  void SetValue(const Symbol&, std::shared_ptr<BaseObject>);

 private:
  ClassMap& class_map_;
  CallTable table_;
  FunctionMap& functions_;
  ScopeLayerTree& tree_;
  Frame frame_;
  std::shared_ptr<ClassObject> current_class_;
  ScopeLayer* current_layer_;
  std::vector<int> current_children_;
  bool returned_{false};
};

#endif  // MYCOMPILLER_FUNCTIONCALLVISITOR_H

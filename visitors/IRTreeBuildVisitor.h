
#ifndef MYCOMPILLER_IRTREEBUILDVISITOR_H
#define MYCOMPILLER_IRTREEBUILDVISITOR_H
#include <TemplateBaseVisitor.h>
#include <SubtreeWrapper.h>
#include <unordered_map>
#include <Symbol.h>
#include <SubtreeWrapper.h>
#include <IRFrameTranslator.h>
#include <BinOperatorType.h>
#include <LogicOperatorType.h>
#include <ClassMap.h>

class IRTreeBuildVisitor
    : public TemplateBaseVisitor<ir_tree::SubtreeWrapper*> {
 public:
  IRTreeBuildVisitor(ClassMap&);
  void Build(Program*);
  std::unordered_map<Symbol, ir_tree::SubtreeWrapper*> GetMethods();

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
  void Visit(LogicOrExpression*) override;
  void Visit(LogicAndExpression*) override;

  void VisitBinaryExpression(BinaryExpression*, ir_tree::BinOperatorType);
  void VisitLogicExpression(BinaryExpression*, ir_tree::LogicOperatorType);

  ir_tree::IRExpression* GetAddress(const Symbol&);

  std::unordered_map<Symbol, ir_tree::SubtreeWrapper*> methods_;
  std::string current_class_name_;
  ir_tree::IRFrameTranslator* current_frame_;
  ClassMap& class_map_;
};

#endif  // MYCOMPILLER_IRTREEBUILDVISITOR_H

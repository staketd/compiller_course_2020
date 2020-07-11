
#ifndef MYCOMPILLER_BASEVISITORS_H
#define MYCOMPILLER_BASEVISITORS_H

#include "include/forward_decl.h"

class BaseASTVisitor {
public:
    virtual void Visit(StatementList*) = 0;
    virtual void Visit(Assignment*) = 0;
    virtual void Visit(AddExpression*) = 0;
    virtual void Visit(MulExpression*) = 0;
    virtual void Visit(DivExpression*) = 0;
    virtual void Visit(SubstractExpression*) = 0;
    virtual void Visit(IdentExpression*) = 0;
    virtual void Visit(NumExpression*) = 0;
    virtual void Visit(ModuloExpression*) = 0;
    virtual void Visit(Program*) = 0;
    virtual void Visit(PrintStatement*) = 0;
    virtual void Visit(ReadStatement*) = 0;
    virtual void Visit(EqualExpression*) = 0;
    virtual void Visit(LessExpression*) = 0;
    virtual void Visit(GreaterExpression*) = 0;
    virtual void Visit(LessOrEqualExpression*) = 0;
    virtual void Visit(GreaterOrEqualExpression*) = 0;
    virtual void Visit(IfStatement*) = 0;
    virtual void Visit(Scope*) = 0;
    virtual void Visit(VariableDeclaration*) = 0;
    virtual void Visit(WhileStatement*) = 0;
    virtual void Visit(CallArgumentList*) = 0;
    virtual void Visit(ClassMethod*) = 0;
    virtual void Visit(MethodArgumentList*) = 0;
    virtual void Visit(ClassBody*) = 0;
    virtual void Visit(MethodCallExpression*) = 0;
    virtual void Visit(ReturnStatement*) = 0;
    virtual void Visit(MethodCallStmt*) = 0;
    virtual void Visit(Class*) = 0;
    virtual void Visit(ClassList*) = 0;
    virtual void Visit(ClassField*) = 0;
    virtual void Visit(ClassMain*) = 0;
    virtual void Visit(ThisExpression*) = 0;
    virtual void Visit(NewExpression*) = 0;
    virtual void Visit(ArrayDeclaration*) = 0;
    virtual void Visit(ArrayAssignment*) = 0;
    virtual void Visit(ArrayExpression*) = 0;
    virtual void Visit(LogicOrExpression*) = 0;
    virtual void Visit(LogicAndExpression*) = 0;
};

namespace ir_tree {

class BaseIRVisitor {
 public:
  virtual void Visit(BinOpExpression*) = 0;
  virtual void Visit(CallExpression*) = 0;
  virtual void Visit(ConstExpression*) = 0;
  virtual void Visit(EseqExpression*) = 0;
  virtual void Visit(MemExpression*) = 0;
  virtual void Visit(NameExpression*) = 0;
  virtual void Visit(TempExpression*) = 0;
  virtual void Visit(ExpStatement*) = 0;
  virtual void Visit(JumpConditionalStatement*) = 0;
  virtual void Visit(JumpStatement*) = 0;
  virtual void Visit(LabelStatement*) = 0;
  virtual void Visit(MoveStatement*) = 0;
  virtual void Visit(SeqStatement*) = 0;
  virtual void Visit(ExpressionList*) = 0;
  virtual void Visit(IRPrintStatement*) = 0;
};

}


#endif  // MYCOMPILLER_BASEVISITORS_H

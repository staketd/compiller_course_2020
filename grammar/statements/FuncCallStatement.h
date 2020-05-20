
#ifndef MYCOMPILLER_FUNCCALLSTATEMENT_H
#define MYCOMPILLER_FUNCCALLSTATEMENT_H
#include <Statement.h>
#include <FuncCallExpression.h>

class FuncCallStatement : public Statement {
 public:
  FuncCallStatement(FuncCallExpression*);
  void AcceptVisitor(BaseVisitor*);
 public:
  FuncCallExpression* expression_;
};

#endif  // MYCOMPILLER_FUNCCALLSTATEMENT_H

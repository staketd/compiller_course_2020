
#ifndef MYCOMPILLER_RETURNSTATEMENT_H
#define MYCOMPILLER_RETURNSTATEMENT_H
#include <Statement.h>
#include <Expression.h>

class ReturnStatement : public Statement {
 public:
  ReturnStatement(Expression*);
  void AcceptVisitor(BaseVisitor*);

 public:
  Expression* expression_;
};

#endif  // MYCOMPILLER_RETURNSTATEMENT_H

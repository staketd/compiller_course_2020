
#ifndef MYCOMPILLER_METHODCALLSTMT_H
#define MYCOMPILLER_METHODCALLSTMT_H
#include <Statement.h>
#include <MethodCallExpression.h>

class MethodCallStmt : public Statement {
 public:
  MethodCallStmt(MethodCallExpression*);
  void AcceptVisitor(BaseVisitor*);
 public:
  MethodCallExpression* expression_;
};

#endif  // MYCOMPILLER_METHODCALLSTMT_H

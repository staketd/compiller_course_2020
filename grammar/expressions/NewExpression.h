
#ifndef MYCOMPILLER_NEWEXPRESSION_H
#define MYCOMPILLER_NEWEXPRESSION_H
#include <Expression.h>
class NewExpression : public Expression {
 public:
  NewExpression(const std::string&);
  void AcceptVisitor(BaseASTVisitor*);

 public:
  std::string type_;
};

#endif  // MYCOMPILLER_NEWEXPRESSION_H

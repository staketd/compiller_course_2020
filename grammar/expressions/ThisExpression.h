
#ifndef MYCOMPILLER_THISEXPRESSION_H
#define MYCOMPILLER_THISEXPRESSION_H
#include <Expression.h>

class ThisExpression : public Expression {
 public:
  void AcceptVisitor(BaseVisitor*);
};

#endif  // MYCOMPILLER_THISEXPRESSION_H

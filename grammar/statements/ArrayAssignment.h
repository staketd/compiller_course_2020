
#ifndef MYCOMPILLER_ARRAYASSIGNMENT_H
#define MYCOMPILLER_ARRAYASSIGNMENT_H
#include <Statement.h>
#include <Expression.h>

class ArrayAssignment : public Statement {
 public:
  ArrayAssignment(const std::string&, Expression*, Expression*);
  void AcceptVisitor(BaseASTVisitor*) override;

 public:
  std::string array_name_;
  Expression* ind_expression_;
  Expression* expression_;
};

#endif  // MYCOMPILLER_ARRAYASSIGNMENT_H

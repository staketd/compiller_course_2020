
#ifndef MYCOMPILLER_VARIABLEDECLARATION_H
#define MYCOMPILLER_VARIABLEDECLARATION_H

#include <Statement.h>
#include <string>

class VariableDeclaration : public Statement {
 public:
  explicit VariableDeclaration(std::string, std::string, Expression*);
  void AcceptVisitor(BaseASTVisitor*) override;

 public:
  std::string type_name_;
  std::string name_;
  Expression* expression_;
};

#endif  // MYCOMPILLER_VARIABLEDECLARATION_H

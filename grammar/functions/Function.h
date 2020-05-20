
#ifndef MYCOMPILLER_FUNCTION_H
#define MYCOMPILLER_FUNCTION_H

#include <BaseASTClass.h>
#include <string>
#include <BaseType.h>
#include <StatementList.h>

class Function : public BaseASTClass {
 public:
  Function(const std::string&, FuncArgumentList*, StatementList*, const std::string&);
  void AcceptVisitor(BaseVisitor*) override;

  std::string name_;
  FuncArgumentList* arguments_;
  StatementList* statements_;
  BaseType* return_type_;
};

#endif  // MYCOMPILLER_FUNCTION_H


#ifndef MYCOMPILLER_CLASSMETHOD_H
#define MYCOMPILLER_CLASSMETHOD_H

#include <BaseASTClass.h>
#include <string>
#include <BaseObject.h>
#include <StatementList.h>

class ClassMethod : public BaseASTClass {
 public:
  ClassMethod(const std::string&, MethodArgumentList*, StatementList*, const std::string&);
  void AcceptVisitor(BaseVisitor*) override;

  std::string name_;
  MethodArgumentList* arguments_;
  StatementList* statements_;
  std::string return_type_;
};

#endif  // MYCOMPILLER_CLASSMETHOD_H

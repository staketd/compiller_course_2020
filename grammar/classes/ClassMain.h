
#ifndef MYCOMPILLER_CLASSMAIN_H
#define MYCOMPILLER_CLASSMAIN_H
#include <BaseASTClass.h>
#include <string>
#include <StatementList.h>

class ClassMain : public BaseASTClass {
 public:
  ClassMain(const std::string&, ClassMethod*);
  void AcceptVisitor(BaseASTVisitor*) override;

 public:
  std::string name_;
  ClassMethod* main_;
};

#endif  // MYCOMPILLER_CLASSMAIN_H

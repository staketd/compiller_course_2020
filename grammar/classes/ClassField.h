
#ifndef MYCOMPILLER_CLASSFIELD_H
#define MYCOMPILLER_CLASSFIELD_H
#include <BaseASTClass.h>
#include <string>

class ClassField : public BaseASTClass {
 public:
  ClassField(const std::string&, const std::string&);
  void AcceptVisitor(BaseASTVisitor*) override;

 public:
  std::string type_;
  std::string name_;
};

#endif  // MYCOMPILLER_CLASSFIELD_H

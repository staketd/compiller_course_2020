
#ifndef MYCOMPILLER_CLASSLIST_H
#define MYCOMPILLER_CLASSLIST_H
#include <BaseASTClass.h>
#include <Class.h>

class ClassList : public BaseASTClass {
 public:
  ClassList() = default;
  void AddClass(Class*);
  void AcceptVisitor(BaseASTVisitor*) override;

 public:
  std::vector<Class*> classes_;
};

#endif  // MYCOMPILLER_CLASSLIST_H

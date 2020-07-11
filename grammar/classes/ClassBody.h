
#ifndef MYCOMPILLER_CLASSBODY_H
#define MYCOMPILLER_CLASSBODY_H
#include <BaseASTClass.h>
#include <vector>
#include <ClassMethod.h>
#include <ClassField.h>

class ClassBody : public BaseASTClass {
 public:
  ClassBody() = default;
  void AddMethod(ClassMethod*);
  void AddField(ClassField*);
  void AcceptVisitor(BaseASTVisitor*) override;

 public:
  std::vector<ClassMethod*> methods_;
  std::vector<ClassField*> fields_;
};

#endif  // MYCOMPILLER_CLASSBODY_H

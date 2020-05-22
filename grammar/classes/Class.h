
#ifndef MYCOMPILLER_CLASS_H
#define MYCOMPILLER_CLASS_H
#include <BaseASTClass.h>
#include <ClassBody.h>

class Class : public BaseASTClass  {
 public:
  Class(const std::string&, ClassBody*);
  void AcceptVisitor(BaseVisitor*) override;

 public:
  std::string name_;
  ClassBody* body_;
};

#endif  // MYCOMPILLER_CLASS_H

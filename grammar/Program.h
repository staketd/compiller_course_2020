#ifndef MYCOMPILLER_PROGRAM_H
#define MYCOMPILLER_PROGRAM_H

#include <ClassBody.h>
#include <Expression.h>

class Program : BaseASTClass {
 public:
  explicit Program(ClassMain*, ClassList*);
  void AcceptVisitor(BaseVisitor*) override;

 public:
  ClassMain* main_;
  ClassList* classes_;
};

#endif  // MYCOMPILLER_PROGRAM_H


#ifndef MYCOMPILLER_ARRAYDECLARATION_H
#define MYCOMPILLER_ARRAYDECLARATION_H
#include <Statement.h>
#include <BaseType.h>

class ArrayDeclaration : public Statement {
 public:
  ArrayDeclaration(const std::string&, const std::string&, size_t);
  void AcceptVisitor(BaseVisitor*) override;

 public:
  size_t size_;
  std::string array_type_;
  std::string name_;
};

#endif  // MYCOMPILLER_ARRAYDECLARATION_H

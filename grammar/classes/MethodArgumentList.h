
#ifndef MYCOMPILLER_METHODARGUMENTLIST_H
#define MYCOMPILLER_METHODARGUMENTLIST_H
#include <BaseASTClass.h>
#include <string>
#include <vector>

class MethodArgumentList : public BaseASTClass {
 public:
  MethodArgumentList() = default;
  void AddArgument(const std::string&, const std::string&);
  void AcceptVisitor(BaseASTVisitor*) override ;

 public:
  std::vector<std::string> types_;
  std::vector<std::string> names_;
};

#endif  // MYCOMPILLER_METHODARGUMENTLIST_H

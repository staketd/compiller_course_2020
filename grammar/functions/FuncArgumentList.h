
#ifndef MYCOMPILLER_FUNCARGUMENTLIST_H
#define MYCOMPILLER_FUNCARGUMENTLIST_H
#include <BaseASTClass.h>
#include <string>
#include <vector>

class FuncArgumentList : public BaseASTClass {
 public:
  FuncArgumentList() = default;
  void AddArgument(const std::string&);
  void AcceptVisitor(BaseVisitor*) override ;

 public:
  std::vector<std::string> names_;
};

#endif  // MYCOMPILLER_FUNCARGUMENTLIST_H

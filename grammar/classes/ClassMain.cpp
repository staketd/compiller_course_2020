
#include "ClassMain.h"

ClassMain::ClassMain(const std::string& name, ClassMethod* method)
    : name_(name), main_(method){
}

void ClassMain::AcceptVisitor(BaseASTVisitor* visitor) {
  visitor->Visit(this);
}

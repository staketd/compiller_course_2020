
#ifndef MYCOMPILLER_TEMPLATEBASEVISITOR_H
#define MYCOMPILLER_TEMPLATEBASEVISITOR_H

#include <BaseVisitors.h>
#include <Expression.h>
#include <BaseIRNode.h>

template <typename T>
class TemplateBaseVisitor : public BaseASTVisitor {
 public:
  T VisitAndReturnValue(BaseASTClass*);

 protected:
  T last_value_set_;
};

namespace ir_tree {
template <typename T>
class TemplateBaseVisitor : public BaseIRVisitor {
 public:
  T VisitAndReturnValue(BaseIRNode*);

 protected:
  T last_value_set_;
};

}

#endif  // MYCOMPILLER_TEMPLATEBASEVISITOR_H

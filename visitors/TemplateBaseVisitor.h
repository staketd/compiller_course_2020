
#ifndef MYCOMPILLER_TEMPLATEBASEVISITOR_H
#define MYCOMPILLER_TEMPLATEBASEVISITOR_H

#include <BaseVisitors.h>
#include <Expression.h>

template <typename T>
class TemplateBaseVisitor : public BaseASTVisitor {
public:
    T VisitAndReturnValue(BaseASTClass*);

protected:
    T last_value_set_;
};


#endif //MYCOMPILLER_TEMPLATEBASEVISITOR_H

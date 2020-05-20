
#ifndef MYCOMPILLER_TEMPLATEBASEVISITOR_H
#define MYCOMPILLER_TEMPLATEBASEVISITOR_H

#include <BaseVisitor.h>
#include <Expression.h>

template <typename T>
class TemplateBaseVisitor : public BaseVisitor {
public:
    T VisitAndSetValue(BaseASTClass*);

protected:
    T last_value_set_;
};


#endif //MYCOMPILLER_TEMPLATEBASEVISITOR_H

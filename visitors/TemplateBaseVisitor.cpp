#include "TemplateBaseVisitor.h"

template <typename T>
T TemplateBaseVisitor<T>::VisitAndSetValue(BaseASTClass* base_element) {
    base_element->AcceptVisitor(this);
    return last_value_set_;
}

template int TemplateBaseVisitor<int>::VisitAndSetValue(BaseASTClass*);
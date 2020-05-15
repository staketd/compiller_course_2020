#include "TemplateBaseVisitor.h"

template <typename T>
T TemplateBaseVisitor<T>::VisitAndSetValue(BaseClass* base_element) {
    base_element->AcceptVisitor(this);
    return last_value_set_;
}

template int TemplateBaseVisitor<int>::VisitAndSetValue(BaseClass*);
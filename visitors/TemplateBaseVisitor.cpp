#include "TemplateBaseVisitor.h"
#include <memory>
#include <BaseType.h>
#include <SubtreeWrapper.h>
#include <IRUnion.h>

template <typename T>
T TemplateBaseVisitor<T>::VisitAndReturnValue(BaseASTClass* base_element) {
  base_element->AcceptVisitor(this);
  return last_value_set_;
}

template int TemplateBaseVisitor<int>::VisitAndReturnValue(BaseASTClass*);

template std::shared_ptr<BaseObject> TemplateBaseVisitor<
    std::shared_ptr<BaseObject>>::VisitAndReturnValue(BaseASTClass*);

template std::shared_ptr<BaseType> TemplateBaseVisitor<
    std::shared_ptr<BaseType>>::VisitAndReturnValue(BaseASTClass*);

template ir_tree::SubtreeWrapper* TemplateBaseVisitor<
    ir_tree::SubtreeWrapper*>::VisitAndReturnValue(BaseASTClass*);

template <typename T>
T ir_tree::TemplateBaseVisitor<T>::VisitAndReturnVisitor(
    BaseIRNode* base_element) {
  base_element->AcceptVisitor(this);
  return last_value_set_;
}

template ir_tree::IRUnion ir_tree::TemplateBaseVisitor<
    ir_tree::IRUnion>::VisitAndReturnVisitor(BaseIRNode*);
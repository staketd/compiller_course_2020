
#ifndef MYCOMPILLER_FUNCTIONTYPE_H
#define MYCOMPILLER_FUNCTIONTYPE_H
#include <BaseType.h>

class FunctionType : public BaseType {
 public:
  FunctionType(std::shared_ptr<BaseType>);
  std::string TypeName() override;
  std::shared_ptr<BaseType> GetReturnType();

 private:
  std::shared_ptr<BaseType> return_type_;
};

#endif  // MYCOMPILLER_FUNCTIONOBJECT_H

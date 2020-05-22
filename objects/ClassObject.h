
#ifndef MYCOMPILLER_CLASSOBJECT_H
#define MYCOMPILLER_CLASSOBJECT_H

#include <BaseObject.h>
#include <FunctionObject.h>
#include <memory>
#include <unordered_map>
#include <Symbol.h>

class ClassObject : public BaseObject {
 public:
  ClassObject(const std::string& name);
  int ToInt() override;
  bool IsUserClass() override;
  std::shared_ptr<BaseObject> GetValue(const Symbol&);
  void SetValue(const Symbol&, std::shared_ptr<BaseObject>);
  void CreateField(const Symbol&, std::shared_ptr<BaseObject>);

 public:
  std::unordered_map<Symbol, std::shared_ptr<BaseObject>> fields_;
};

#endif  // MYCOMPILLER_CLASSTYPE_H

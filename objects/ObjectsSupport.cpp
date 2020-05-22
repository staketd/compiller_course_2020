#include <BaseObject.h>
#include <Integer.h>
#include <BoolObject.h>
#include <ClassObject.h>

inline std::shared_ptr<BaseObject> CreateObjectPtr(const std::string type_name) {
  if (type_name == "Integer") {
    return std::make_shared<Integer>();
  } else if (type_name == "Bool") {
    return std::make_shared<BoolObject>();
  }
  return std::make_shared<ClassObject>(type_name);
}


#ifndef MYCOMPILLER_ARRAYOBJECT_H
#define MYCOMPILLER_ARRAYOBJECT_H
#include <BaseObject.h>
#include <vector>
#include <memory>

class ArrayObject : public BaseObject {
 public:
  ArrayObject(const std::string, size_t size,
              const std::vector<std::shared_ptr<BaseObject>>&);
  int ToInt() override;

 public:
  size_t size_;
  std::string name_;
  std::vector<std::shared_ptr<BaseObject>> array_;
};

#endif  // MYCOMPILLER_ARRAYOBJECT_H

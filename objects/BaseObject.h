
#ifndef MYCOMPILLER_BASEOBJECT_H
#define MYCOMPILLER_BASEOBJECT_H
#include <string>

class BaseObject {
 public:
  virtual int ToInt() = 0;
  virtual ~BaseObject() = default;

  BaseObject(const std::string& type) : type_(type) {
  }

  virtual bool IsInteger() {
    return false;
  }

  virtual bool IsBool() {
    return false;
  }

  virtual bool IsFunction() {
    return false;
  }

  virtual bool IsUserClass() {
    return false;
  }

  virtual std::string GetType() {
    return type_;
  }

 private:
  std::string type_;
};

#endif  // MYCOMPILLER_BASEOBJECT_H

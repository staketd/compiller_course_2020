
#ifndef MYCOMPILLER_BASEOBJECT_H
#define MYCOMPILLER_BASEOBJECT_H

class BaseType {
 public:
  virtual int ToInt() = 0;
  virtual ~BaseType() = default;
  virtual BaseType* GetType() = 0;

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
};

#endif  // MYCOMPILLER_BASEOBJECT_H

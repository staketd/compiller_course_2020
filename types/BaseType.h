
#ifndef MYCOMPILLER_BASETYPE_H
#define MYCOMPILLER_BASETYPE_H
#include <string>
#include <memory>

class BaseType {
 public:
  enum class Type {
    Integer,
    Bool,
    Void,
    Class,
    Function,
  };

  bool IsBool();
  bool IsInteger();
  bool IsClass();
  bool IsFunction();
  bool IsVoid();

  virtual bool IsSameWith(std::shared_ptr<BaseType>);
  virtual std::string TypeName() = 0;

  BaseType(Type type);

 public:
  Type type_;
};

#endif  // MYCOMPILLER_BASETYPE_H

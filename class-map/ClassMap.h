
#ifndef MYCOMPILLER_CLASSMAP_H
#define MYCOMPILLER_CLASSMAP_H
#include <Class.h>
#include <Symbol.h>
#include <unordered_map>
#include <ClassLayout.h>

class ClassMap {
 public:
  ClassMap() = default;
  void SetClass(const Symbol&, Class*);
  Class* GetClass(const Symbol&);
  void SetClassLayout(const Symbol&, ClassLayout*);
  ClassLayout* GetClassLayout(const Symbol&);
  bool HasClass(const Symbol&);

 private:
  std::unordered_map<Symbol, Class*> classes_;
  std::unordered_map<Symbol, ClassLayout*> class_layouts_;
};

#endif  // MYCOMPILLER_CLASSMAP_H

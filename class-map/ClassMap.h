
#ifndef MYCOMPILLER_CLASSMAP_H
#define MYCOMPILLER_CLASSMAP_H
#include <Class.h>
#include <Symbol.h>
#include <unordered_map>

class ClassMap {
 public:
  ClassMap() = default;
  void SetClass(const Symbol&, Class*);
  Class* GetClass(const Symbol&);

 private:
  std::unordered_map<Symbol, Class*> classes_;
};

#endif  // MYCOMPILLER_CLASSMAP_H

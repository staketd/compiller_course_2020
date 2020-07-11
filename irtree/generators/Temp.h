
#ifndef MYCOMPILLER_TEMP_H
#define MYCOMPILLER_TEMP_H
#include <string>
namespace ir_tree {

class Temp {
 public:
  Temp();
  Temp(const std::string&);
  std::string ToString() const;

 private:
  std::string name_;
  static size_t counter;
};


} // namespace ir_tree

#endif  // MYCOMPILLER_TEMP_H

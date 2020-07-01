
#ifndef MYCOMPILLER_LABEL_H
#define MYCOMPILLER_LABEL_H
#include <string>

namespace ir_tree {

class Label {
 public:
  Label();
  explicit Label(const std::string&);

  std::string ToString() const;

 private:
  std::string label_;
  static size_t counter;
};

} // namespace IRTree

#endif  // MYCOMPILLER_LABEL_H


#ifndef MYCOMPILLER_CLASSLAYOUT_H
#define MYCOMPILLER_CLASSLAYOUT_H
#include <Symbol.h>
#include <unordered_map>

class ClassLayout {
 public:
  ClassLayout(const std::string&);
  void AddField(const Symbol&);
  size_t GetOffset(const Symbol&);
  bool HasField(const Symbol&) const;
  std::string GetName() const;
 private:
  std::unordered_map<Symbol, size_t> offsets_;
  size_t current_offset_;
  size_t class_size_;
  std::string class_name_;
};

#endif  // MYCOMPILLER_CLASSLAYOUT_H

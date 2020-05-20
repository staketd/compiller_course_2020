
#ifndef MYCOMPILLER_FRAME_H
#define MYCOMPILLER_FRAME_H
#include <vector>

class Frame {
 public:
  Frame() = default;
  Frame(const std::vector<int>&);
  void SetParams(const std::vector<int>&);
  void SetValue(int index, int value);

  int GetValue(int index);
  size_t AllocVariable();

  void BeginScope();
  void EndScope();

  int GetReturnValue();
  void SetParentReturnValue(int value);

  bool HasParent();
  void SetParent(Frame*);

  Frame(const Frame&) = delete;
  Frame operator=(const Frame&) = delete;

  Frame(Frame &&);

 private:
  void SetResultValue(int);

 private:
  int result_;
  std::vector<int> variables_;
  std::vector<int> params_;
  std::vector<size_t> scope_sizes_;
  Frame* parent_;
};

#endif  // MYCOMPILLER_FRAME_H

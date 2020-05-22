
#ifndef MYCOMPILLER_FRAME_H
#define MYCOMPILLER_FRAME_H
#include <vector>
#include <ClassObject.h>

class Frame {
 public:
  Frame() = default;
  Frame(const std::vector<std::shared_ptr<BaseObject>>&);
  void SetParams(const std::vector<std::shared_ptr<BaseObject>>&);

  void SetValue(int index, std::shared_ptr<BaseObject> value);

  std::shared_ptr<BaseObject> GetValue(int index);
  size_t AllocVariable(std::shared_ptr<BaseObject>);

  void BeginScope();
  void EndScope();

  std::shared_ptr<BaseObject> GetReturnValue();
  void SetParentReturnValue(std::shared_ptr<BaseObject> value);

  bool HasParent();
  void SetParent(Frame*);

  Frame(const Frame&) = delete;
  Frame operator=(const Frame&) = delete;

  Frame(Frame &&);

 private:
  void SetResultValue(std::shared_ptr<BaseObject>);

 private:
  std::shared_ptr<BaseObject> result_;
  std::vector<std::shared_ptr<BaseObject>> variables_;
  std::vector<std::shared_ptr<BaseObject>> params_;
  std::vector<size_t> scope_sizes_;
  Frame* parent_;
};

#endif  // MYCOMPILLER_FRAME_H

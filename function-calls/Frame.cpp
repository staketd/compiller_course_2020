
#include "Frame.h"

bool Frame::HasParent() {
  return parent_ != nullptr;
}

void Frame::SetParentReturnValue(int value) {
  if (HasParent()) {
    parent_->SetResultValue(value);
  }
}

void Frame::SetResultValue(int value) {
  result_ = value;
}

int Frame::GetReturnValue() {
  return result_;
}
void Frame::SetParams(const std::vector<int>& params) {
  params_ = params;
}

void Frame::SetValue(int index, int value) {
  if (index >= 0) {
    variables_.at(index) = value;
  } else {
    params_.at(-index - 1) = value;
  }
}

int Frame::GetValue(int index) {
  if (index >= 0) {
    return variables_.at(index);
  }
  return params_.at(-index - 1);
}

size_t Frame::AllocVariable() {
  variables_.push_back(0);
  return variables_.size() - 1;
}

void Frame::BeginScope() {
  scope_sizes_.push_back(variables_.size());
}

void Frame::EndScope() {
  variables_.resize(scope_sizes_.back());
  scope_sizes_.pop_back();
}
Frame::Frame(const std::vector<int>& params) : params_(params) {
}

Frame::Frame(Frame&& other) {
  params_ = other.params_;
  parent_ = other.parent_;
  result_ = other.result_;
  variables_ = other.variables_;
  scope_sizes_ = other.scope_sizes_;
}
void Frame::SetParent(Frame* parent) {
  parent_ = parent;
}


#ifndef MYCOMPILLER_ELEMENTSET_H
#define MYCOMPILLER_ELEMENTSET_H
#include <vector>
#include <bitset>
#include <unordered_map>
#include <iostream>

template <typename T, size_t N>
class ElementSet {
 public:
  ElementSet() = delete;
  ElementSet(const std::vector<T>&);
  class Set {
   public:
    Set() = default;
    Set(const Set&) = default;

    Set Union(const Set&);
    void SelfUnion(const Set&);
    Set Intersect(const Set&);
    Set Complement(const Set&);
    bool IsDifferFrom(const Set&);

    std::bitset<N> GetMask() const;

   private:
    Set(const std::bitset<N>&);
    std::bitset<N> mask_;
    friend ElementSet<T, N>;
  };

  std::vector<T> GetElements(const Set&);
  Set GetSet(const std::vector<T>&);
  std::vector<size_t> GetIndexes(const Set&);
  std::vector<size_t> GetIndexes(const std::vector<T>&);
  size_t GetIndex(const T&);

 private:
  std::vector<T> elements_;
  std::unordered_map<T, size_t> positions_;
};

using ElementSetk = ElementSet<std::string, 50>;
using Set = ElementSetk::Set;

template <typename T, size_t N>
typename ElementSet<T, N>::Set ElementSet<T, N>::Set::Union(
    const ElementSet::Set& set) {
  return Set(mask_ | set.mask_);
}

template <typename T, size_t N>
ElementSet<T, N>::Set::Set(const std::bitset<N>& bitset) : mask_(bitset) {
}

template <typename T, size_t N>
typename ElementSet<T, N>::Set ElementSet<T, N>::Set::Intersect(
    const ElementSet::Set& set) {
  return Set(set.mask_ & mask_);
}

template <typename T, size_t N>
typename ElementSet<T, N>::Set ElementSet<T, N>::Set::Complement(
    const ElementSet::Set& set) {
  return Set(mask_ ^ (mask_ & set.mask_));
}

template <typename T, size_t N>
std::bitset<N> ElementSet<T, N>::Set::GetMask() const {
  return mask_;
}

template <typename T, size_t N>
bool ElementSet<T, N>::Set::IsDifferFrom(const ElementSet::Set& set) {
  return (set.mask_ ^ mask_).any();
}

template <typename T, size_t N>
void ElementSet<T, N>::Set::SelfUnion(const Set& set) {
  mask_ |= set.mask_;
}

template <typename T, size_t N>
std::vector<T> ElementSet<T, N>::GetElements(const Set& set) {
  std::vector<T> result;
  for (size_t i = 0; i < elements_.size(); ++i) {
    if (set.mask_[i]) {
      result.push_back(elements_[i]);
    }
  }
  return result;
}

template <typename T, size_t N>
ElementSet<T, N>::ElementSet(const std::vector<T>& elements)
    : elements_(elements) {
  size_t ind = 0;
  for (auto x : elements_) {
    positions_[x] = ind++;
  }
}

template <typename T, size_t N>
typename ElementSet<T, N>::Set ElementSet<T, N>::GetSet(
    const std::vector<T>& elements) {
  std::bitset<N> set;
  for (auto x : elements) {
    set.set(positions_[x]);
  }
  return Set(set);
}

template <typename T, size_t N>
std::vector<size_t> ElementSet<T, N>::GetIndexes(const Set& set) {
  std::vector<size_t> result;
  for (size_t i = 0; i < elements_.size(); ++i) {
    if (set.mask_[i]) {
      result.push_back(i);
    }
  }
  return result;
}

template <typename T, size_t N>
std::vector<size_t> ElementSet<T, N>::GetIndexes(
    const std::vector<T>& elements) {
  std::vector<size_t> result;
  for (auto x : elements) {
    result.push_back(positions_[x]);
  }
  return result;
}

template <typename T, size_t N>
size_t ElementSet<T, N>::GetIndex(const T& elem) {
  return positions_[elem];
}

#endif  // MYCOMPILLER_ELEMENTSET_H


#ifndef MYCOMPILLER_TRACE_H
#define MYCOMPILLER_TRACE_H
#include <Block.h>
namespace ir_tree {
class Trace {
 public:
  Trace() = default;
  void AddBlock(const Block&);
  std::vector<Block>& GetBlocks();
 private:
  std::vector<Block> blocks_;
};
}  // namespace ir_tree

#endif  // MYCOMPILLER_TRACE_H

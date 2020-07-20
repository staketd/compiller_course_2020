
#ifndef MYCOMPILLER_BLOCK_H
#define MYCOMPILLER_BLOCK_H
#include <IRStatement.h>
#include <LabelStatement.h>
#include <vector>
#include <JumpConditionalStatement.h>
#include <JumpStatement.h>
namespace ir_tree {
class Block {
 public:
  Block();
  LabelStatement* GetLabel();
  IRStatement* GetJump();
  void AddStatement(IRStatement*);
  std::vector<IRStatement*>& GetStatements();
  void SetLabel(LabelStatement*);
  void SetJump(JumpConditionalStatement*);
  void SetJump(JumpStatement*);

 public:
  bool last_block_;
 private:
  LabelStatement* label_;
  IRStatement* jump_;
  std::vector<IRStatement*> statements_;
};
}

#endif  // MYCOMPILLER_BLOCK_H

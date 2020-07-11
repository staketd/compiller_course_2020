
#ifndef MYCOMPILLER_IRFRAMETRANSLATOR_H
#define MYCOMPILLER_IRFRAMETRANSLATOR_H
#include <Symbol.h>
#include <Address.h>
#include <unordered_map>
#include <vector>

namespace ir_tree {

class IRFrameTranslator {
 public:
  IRFrameTranslator(const Symbol&);

  void AddLocalVariable(const Symbol&, size_t = kWordSize);
  void AddArgument(const Symbol&, size_t = kWordSize);

  void BeginScope();
  void EndScope();

  Address* FramePointer();
  Address* GetAddress(const Symbol&);

  Address* GetReturnValueAddress();
  void AddReturnAddress();

 private:
  void AddVariable(Symbol, int);

  const static std::string kReturnAddress;
  const static std::string kFramePointerAddress;
  const static std::string kReturnValueAddress;
  const static int kWordSize;

  std::unordered_map<Symbol, std::vector<Address*>> addresses_;

  int local_offset_;
  int arg_offset_;

  std::vector<Symbol> scopes_symbols_stack_;

  Symbol function_name_;
};


}  // namespace ir_tree

#endif  // MYCOMPILLER_IRFRAMETRANSLATOR_H

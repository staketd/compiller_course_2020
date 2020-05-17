#ifndef MYCOMPILLER_SCOPELAYER_H
#define MYCOMPILLER_SCOPELAYER_H

#include <unordered_map>
#include <Symbol.h>
#include <memory>
#include <BaseObject.h>
#include <vector>

class ScopeLayer : public std::enable_shared_from_this<ScopeLayer> {
 public:
  ScopeLayer();
  explicit ScopeLayer(ScopeLayer*);

  void DeclareVariable(const Symbol&);
  std::shared_ptr<BaseObject> GetValue(const Symbol&);

  void SetValue(const Symbol&, const std::shared_ptr<BaseObject>&);
  bool HasSymbol(const Symbol&);

  ScopeLayer* GetParent() const;
  ScopeLayer* CreateChildren();

  ScopeLayer* GetChildren(size_t);
  void IncreaseOffset();

 private:
  ScopeLayer* FindLayerWithSymbol(const Symbol&);

 private:
  std::unordered_map<Symbol, std::shared_ptr<BaseObject>> values_;
  std::unordered_map<Symbol, size_t> offsets_;
  ScopeLayer* parent_;
  std::vector<Symbol> variable_declaration_order_;
  size_t offset_now_{0};
  std::vector<ScopeLayer*> children_;
};

#endif  // MYCOMPILLER_SCOPELAYER_H

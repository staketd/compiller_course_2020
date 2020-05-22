#ifndef MYCOMPILLER_SCOPELAYER_H
#define MYCOMPILLER_SCOPELAYER_H

#include <unordered_map>
#include <Symbol.h>
#include <memory>
#include <BaseType.h>
#include <vector>

class ScopeLayer : public std::enable_shared_from_this<ScopeLayer> {
 public:
  ScopeLayer();
  explicit ScopeLayer(ScopeLayer*);

  void DeclareSymbol(const Symbol&, std::shared_ptr<BaseType>);
  std::shared_ptr<BaseType> GetType(const Symbol& symbol);

  void SetType(const Symbol& symbol, const std::shared_ptr<BaseType>& obj);
  bool HasSymbol(const Symbol&);

  ScopeLayer* GetParent() const;
  ScopeLayer* CreateChildren();

  ScopeLayer* GetChildren(size_t);

  bool WasDeclared(const Symbol&);

 private:
  ScopeLayer* FindLayerWithSymbol(const Symbol&);

 private:
  std::unordered_map<Symbol, std::shared_ptr<BaseType>> values_;
  std::unordered_map<Symbol, size_t> offsets_;
  ScopeLayer* parent_;
  std::vector<Symbol> variable_declaration_order_;
  std::vector<ScopeLayer*> children_;
};

#endif  // MYCOMPILLER_SCOPELAYER_H

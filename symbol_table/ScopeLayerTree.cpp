
#include "ScopeLayerTree.h"

ScopeLayerTree::ScopeLayerTree(ScopeLayer* root) : root_(root) {
}

ScopeLayer* ScopeLayerTree::GetRoot() const {
    return root_;
}

void ScopeLayerTree::AddMapping(const Symbol& symb, ScopeLayer* layer) {
  functions_[symb] = layer;
}

ScopeLayer* ScopeLayerTree::Get(const Symbol& symb) {
  return functions_[symb];
}

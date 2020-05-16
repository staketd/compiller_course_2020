
#include "ScopeLayerTree.h"

ScopeLayerTree::ScopeLayerTree(ScopeLayer* root) : root_(root) {
}

ScopeLayer* ScopeLayerTree::GetRoot() const {
    return root_;
}

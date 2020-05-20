
#ifndef MYCOMPILLER_SCOPELAYERTREE_H
#define MYCOMPILLER_SCOPELAYERTREE_H

#include <ScopeLayer.h>
#include <ScopeLayerTree.h>
#include <unordered_map>
#include <Symbol.h>

class ScopeLayerTree {
public:
    explicit ScopeLayerTree(ScopeLayer*);
    [[nodiscard]] ScopeLayer* GetRoot() const;
    void AddMapping(const Symbol&, ScopeLayer*);
    ScopeLayer* Get(const Symbol&);

private:
    ScopeLayer* root_;
    std::unordered_map<Symbol, ScopeLayer*> functions_;
};


#endif //MYCOMPILLER_SCOPELAYERTREE_H

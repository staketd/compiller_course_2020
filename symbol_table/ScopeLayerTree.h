
#ifndef MYCOMPILLER_SCOPELAYERTREE_H
#define MYCOMPILLER_SCOPELAYERTREE_H

#include <ScopeLayer.h>

class ScopeLayerTree {
public:
    explicit ScopeLayerTree(ScopeLayer*);
    [[nodiscard]] ScopeLayer* GetRoot() const;

private:
    ScopeLayer* root_;
};


#endif //MYCOMPILLER_SCOPELAYERTREE_H

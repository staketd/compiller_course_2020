#ifndef MYCOMPILLER_SCOPELAYER_H
#define MYCOMPILLER_SCOPELAYER_H

#include <unordered_map>
#include <Symbol.h>
#include <memory>
#include <BaseObject.h>

class ScopeLayer : public std::enable_shared_from_this<ScopeLayer> {
public:
    ScopeLayer();
    explicit ScopeLayer(ScopeLayer*);

    void DeclareVariable(const Symbol&);
    std::shared_ptr<BaseObject> GetValue(const Symbol&);

    void SetValue(const Symbol&, const std::shared_ptr<BaseObject>&);
    bool HasSymbol(const Symbol&);

    ScopeLayer* GetParent() const;
private:
    ScopeLayer* FindLayerWithSymbol(const Symbol&);

private:
    std::unordered_map<Symbol, std::shared_ptr<BaseObject>> values_;
    ScopeLayer* parent_;

};


#endif //MYCOMPILLER_SCOPELAYER_H

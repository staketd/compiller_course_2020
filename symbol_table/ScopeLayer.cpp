#include "ScopeLayer.h"
#include <UninitObject.h>

ScopeLayer::ScopeLayer() : parent_(nullptr) {
}

void ScopeLayer::SetValue(const Symbol& symbol, const std::shared_ptr<BaseObject>& obj) {
    ScopeLayer* layer_with_variable = FindLayerWithSymbol(symbol);
    if (layer_with_variable == nullptr) {
        throw std::runtime_error("Variable \"" + symbol.GetName() + "\" is not declared");
    }
    layer_with_variable->values_[symbol] = obj;
}

bool ScopeLayer::HasSymbol(const Symbol& symbol) {
    return values_.find(symbol) != values_.end();
}

void ScopeLayer::DeclareVariable(const Symbol& symbol) {
    if (values_.find(symbol) != values_.end()) {
        throw std::runtime_error("Redeclaration of variable \"" + symbol.GetName() + "\"");
    }
    values_[symbol] = std::make_shared<UninitObject>();
}

ScopeLayer* ScopeLayer::FindLayerWithSymbol(const Symbol& symbol) {
    ScopeLayer* now_layer = this;
    while (now_layer != nullptr && !now_layer->HasSymbol(symbol)) {
        now_layer = now_layer->parent_;
    }
    return now_layer;
}

std::shared_ptr<BaseObject> ScopeLayer::GetValue(const Symbol& symbol) {
    ScopeLayer* layer_with_variable = FindLayerWithSymbol(symbol);
    if (layer_with_variable == nullptr) {
        throw std::runtime_error("Variable \"" + symbol.GetName() + "\" is not declared");
    }
    return layer_with_variable->values_[symbol];
}

ScopeLayer::ScopeLayer(ScopeLayer* parent) : parent_(parent) {
}

ScopeLayer* ScopeLayer::GetParent() const {
    return parent_;
}



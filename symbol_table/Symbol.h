
#ifndef MYCOMPILLER_SYMBOL_H
#define MYCOMPILLER_SYMBOL_H

#include <string>

class Symbol {
public:
    explicit Symbol(std::string);
    [[nodiscard]] std::string GetName() const;
private:
    std::string name_;
};

namespace std {
    template<>
    struct hash<Symbol> {
        std::size_t operator()(const Symbol& symb) const {
            return std::hash<std::string>()(symb.GetName());
        }
    };
}
#endif //MYCOMPILLER_SYMBOL_H

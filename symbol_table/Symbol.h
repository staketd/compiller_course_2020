
#ifndef MYCOMPILLER_SYMBOL_H
#define MYCOMPILLER_SYMBOL_H

#include <string>

class Symbol {
public:
    explicit Symbol(std::string);
    [[nodiscard]] std::string GetName() const;

    bool operator==(const Symbol&) const;
    bool operator!=(const Symbol&) const;

    Symbol(const Symbol&);
private:
    std::string name_;
};

namespace std {
    template<>
    struct hash<Symbol> {
        std::size_t operator()(const Symbol& symb) const {
            return hash<string>()(symb.GetName());
        }
    };
}
#endif //MYCOMPILLER_SYMBOL_H

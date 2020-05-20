#ifndef MYCOMPILLER_READSTATEMENT_H
#define MYCOMPILLER_READSTATEMENT_H

#include <Statement.h>
#include <string>

class ReadStatement: public Statement {
public:
    explicit ReadStatement(std::string var);
    void AcceptVisitor(BaseVisitor*) override;
    [[nodiscard]] std::string GetVariableName() const;
private:
    std::string variable_;
};


#endif //MYCOMPILLER_READSTATEMENT_H

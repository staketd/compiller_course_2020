
#ifndef MYCOMPILLER_DECLARESTATEMENT_H
#define MYCOMPILLER_DECLARESTATEMENT_H

#include <Statement.h>
#include <string>

class DeclareStatement : public Statement {
public:
    explicit DeclareStatement(std::string);
    void AcceptVisitor(BaseVisitor*) override;
public:
    std::string name_;
};


#endif //MYCOMPILLER_DECLARESTATEMENT_H

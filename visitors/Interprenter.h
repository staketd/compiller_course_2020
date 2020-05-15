
#ifndef MYCOMPILLER_INTERPRENTER_H
#define MYCOMPILLER_INTERPRENTER_H

#include <TemplateBaseVisitor.h>
#include <map>

class Interprenter: public TemplateBaseVisitor<int> {
public:
    Interprenter();
    void ExecuteCode(Program*);

private:
    void Visit(StatementList*) override;
    void Visit(Assignment*) override;
    void Visit(AddExpression*) override;
    void Visit(MulExpression*) override;
    void Visit(DivExpression*) override;
    void Visit(SubstractExpression*) override;
    void Visit(IdentExpression*) override;
    void Visit(NumExpression*) override;
    void Visit(Program*) override;
    void Visit(PrintStatement*) override;
    void Visit(ReadStatement*) override;
    void Visit(EqualExpression*) override;
    void Visit(LessExpression*) override;
    void Visit(GreaterExpression*) override;
    void Visit(LessOrEqualExpression*) override;
    void Visit(GreaterOrEqualExpression*) override;
    void Visit(IfStatement*) override;

    std::map<std::string, int> variables_;
};


#endif //MYCOMPILLER_INTERPRENTER_H

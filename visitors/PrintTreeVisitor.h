#ifndef MYCOMPILLER_PRINTTREEVISITOR_H
#define MYCOMPILLER_PRINTTREEVISITOR_H


#include "BaseVisitor.h"
#include <fstream>

class PrintTreeVisitor: BaseVisitor {
public:
    explicit PrintTreeVisitor(const std::string& filename);
    void PrintProgram(Program*);
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
    void Visit(Scope*) override;
    void PrintTabs();
    size_t tabs_num_;
    std::ofstream stream_;
};


#endif //MYCOMPILLER_PRINTTREEVISITOR_H

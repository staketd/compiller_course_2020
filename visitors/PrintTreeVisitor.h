#ifndef MYCOMPILLER_PRINTTREEVISITOR_H
#define MYCOMPILLER_PRINTTREEVISITOR_H


#include "BaseVisitor.h"
#include <fstream>

class PrintTreeVisitor: BaseVisitor {
public:
    PrintTreeVisitor(const std::string& filename);
    void PrintProgram(Program*);
private:
    void Visit(AssignmentList*) override;
    void Visit(Assignment*) override;
    void Visit(AddExpression*) override;
    void Visit(MulExpression*) override;
    void Visit(DivExpression*) override;
    void Visit(SubstractExpression*) override;
    void Visit(IdentExpression*) override;
    void Visit(NumExpression*) override;
    void Visit(Program*) override;
    void PrintTabs();
    size_t tabs_num_;
    std::ofstream stream_;
};


#endif //MYCOMPILLER_PRINTTREEVISITOR_H

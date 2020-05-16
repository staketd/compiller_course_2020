
#ifndef MYCOMPILLER_INTERPRENTER_H
#define MYCOMPILLER_INTERPRENTER_H

#include <TemplateBaseVisitor.h>
#include <Table.h>
#include <ScopeLayer.h>

class Interprenter: public TemplateBaseVisitor<int> {
public:
    explicit Interprenter(ScopeLayer*);
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
    void Visit(Scope*) override;
    void Visit(VariableDeclaration*) override;
    void Visit(ModuloExpression*) override;
    void Visit(WhileStatement*) override;

    ScopeLayer* current_layer_;
};


#endif //MYCOMPILLER_INTERPRENTER_H

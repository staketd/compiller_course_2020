
#ifndef MYCOMPILLER_INTERPRENTER_H
#define MYCOMPILLER_INTERPRENTER_H

#include <BaseVisitor.h>
#include <map>

class Interprenter: public BaseVisitor {
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

    void SetLastValue(int value);

    void UnsetLastValue();
    std::map<std::string, int> variables_;


    int last_calculated_value_;
    bool last_value_is_set_;
public:
    Interprenter();
    int ExecuteCode(Program*);
};


#endif //MYCOMPILLER_INTERPRENTER_H

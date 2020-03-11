#ifndef MYCOMPILLER_PROGRAM_H
#define MYCOMPILLER_PROGRAM_H

#include <AssignmentList.h>
#include <Expression.h>

class Program {
public:
    Program(AssignmentList*, Expression*);
    AssignmentList* assignments_;
    Expression* expression_;
};


#endif //MYCOMPILLER_PROGRAM_H

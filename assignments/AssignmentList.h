
#ifndef MYCOMPILLER_ASSIGNMENTLIST_H
#define MYCOMPILLER_ASSIGNMENTLIST_H

#include <Assignment.h>
#include <vector>

class AssignmentList: BaseClass {
public:
    void AddAssignment(Assignment*);
    void AcceptVisitor(BaseVisitor*) override;
    std::vector<Assignment*> assignments_;
};


#endif //MYCOMPILLER_ASSIGNMENTLIST_H

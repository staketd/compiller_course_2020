
#ifndef MYCOMPILLER_INTEGER_H
#define MYCOMPILLER_INTEGER_H

#include <BaseObject.h>

class Integer : public BaseObject {
public:
    Integer(int val);
    int ToInt() override;

private:
    int value_;
};


#endif //MYCOMPILLER_INTEGER_H

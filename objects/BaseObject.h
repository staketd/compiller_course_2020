
#ifndef MYCOMPILLER_BASEOBJECT_H
#define MYCOMPILLER_BASEOBJECT_H

class BaseObject {
public:
    virtual int ToInt() = 0;
    virtual ~BaseObject() = default;
};

#endif //MYCOMPILLER_BASEOBJECT_H

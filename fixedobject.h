#ifndef FIXEDOBJECT_H
#define FIXEDOBJECT_H
#include"object.h"
#include"room.h"
class player;
class fixedobject : public object
{
public:
    fixedobject(string,string,string,object*,bool,room*);
    fixedobject(string,string,string,object*,bool);
    bool act(agent*,bool);
};

#endif // FIXEDOBJECT_H

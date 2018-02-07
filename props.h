#ifndef PROPS_H
#define PROPS_H
class room;
class player;
#include"object.h"



class props : public object
{
   public:
       props(string,string,string,object*,bool ,room*);
       props(string,string,string,object*,bool);
       bool act(agent*,bool);
};

#endif // PROPS_H

#ifndef TREASURE_H
#define TREASURE_H
#include "player.h"
class object;

class treasure : public object
{
public:
    treasure(string,string,string,object*,bool,room*);
    bool act(agent*,bool);
};

#endif // TREASURE_H

#ifndef PLAYER_H
#define PLAYER_H
#include"agent.h"
class room;
class object;


class player : public agent
{
public:
    player(string,string,string,room*);
    void getobject(room*);
    void dropobject(room*);
    void usefixedobject(room*);
    void printholding();
    bool act();


};

#endif // PLAYER_H

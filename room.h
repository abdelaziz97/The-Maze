#ifndef ROOM_H
#define ROOM_H
#include <iostream>
#include<map>
#include<vector>
#include"agent.h"
#include"object.h"
#include"props.h"
#include"fixedobject.h"
using namespace std;

class agent;

class room
{
private:
    string name;
    string desc;


public:
    room();
    room(string , string );
    string getname();
    string getdesc();
    void link(room *, string);
    room *getlinked(string);
    void printlinked();
    void enter(agent*);
    void leave(agent*);
    void entermonster(agent*);
    void leavemonster(agent*);
    void printagents();
    void printfixedobjects();
    void printprops();
    bool checkthis();
    object* cur_object=NULL;
    vector<object*> fixed_object;
    vector<object*> cur_props;
    map<string,room*> arr;
    map<agent*,bool> cur_agents;
    map<agent*,bool> cur_monsters;
    ~room();


};

#endif // ROOM_H

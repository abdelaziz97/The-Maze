#ifndef OBJECT_H
#define OBJECT_H
#include<iostream>
using namespace std;
class room;
class player;
class agent;
class object
{
protected:
    string name;
    string desc;
    string key;
    object* hidden_value;
    bool state;
public:
    virtual bool act(agent*,bool)=0;
    string getname()
    {
        return name;
    }
    string getdesc()
    {
        return desc;
    }
    string getkey()
    {
        return key;
    }
    object* gethiddenvalue()
    {
        return hidden_value;
    }
    bool getstate()
    {
        return state;
    }
};

#endif // OBJECT_H

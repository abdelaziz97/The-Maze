#include "room.h"
#include <iostream>
#include"agent.h"

using namespace std;

room::room()
{

}
room::room(string nam,string des)
{
    name=nam;
    desc=des;
    arr["north"]=NULL;
    arr["south"]=NULL;
    arr["east"]=NULL;
    arr["west"]=NULL;
}
void room::link(room *r, string dir)
{
    arr[dir]=r;
}
room *room::getlinked(string dir)
{

    if(arr[dir]!=NULL)
    {
        return arr[dir];
    }
    return NULL;

}
string room::getname()
{
    return name;
}
string room::getdesc()
{
    return desc;
}
void room::printlinked()
{
    map<string,room*>::iterator it;
    for(it=arr.begin() ; it!=arr.end();it++)
    {
        if(it->second!=NULL)
        {
            cout<<"Go to ("<<it->first<<") "<<(it->second)->name<<endl;
        }
    }
}
void room::enter(agent *ag)
{
    cur_agents[ag]=true;
}
void room::leave(agent *ag)
{
    map<agent*,bool>::iterator it;
    it=cur_agents.find(ag);
    cur_agents.erase(it);
}
void room::entermonster(agent *ag)
{
    cur_monsters[ag]=true;
}
void room::leavemonster(agent *ag)
{
    map<agent*,bool>::iterator it;
    it=cur_monsters.find(ag);
    cur_monsters.erase(it);
}
void room::printagents()
{
    map<agent*,bool>::iterator it;
    cout<<"Occupants of this room is/are.... \n"<<endl;
    for(it=cur_agents.begin() ; it!=cur_agents.end() ; it++)
    {
        if(it->second)
        {
            cout<< (it->first)->getname()<< ", " << (it->first)->getdisc()<<endl;
        }
    }

}
void room::printfixedobjects()
{
    vector<object*>::iterator it;
    cout<<"This room has some fixed object(s)...."<<endl;
    bool check=true;
    for(it=fixed_object.begin() ; it!=fixed_object.end() ; it++)
    {
        cout<<(*it)->getname()<<", "<<(*it)->getdesc()<<endl;
        check=false;
    }
    if(check){cout<<"Nothing"<<endl;}
}
void room::printprops()
{
    vector<object*>::iterator it;
    cout<<"This room has some prop(s)...."<<endl;
    bool check=true;
    for(it=cur_props.begin() ; it!=cur_props.end() ; it++)
    {
        cout<<(*it)->getname()<<", "<<(*it)->getdesc()<<endl;
        check=false;
    }
    if(check){cout<<"Nothing";}
}

bool room :: checkthis()
{
    bool s;
    agent* p ;
    if ( p.type ==false )
        s = false;
    else
    {
        s = true;
    }

    return s;
}
room::~room()
{

}



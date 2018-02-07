#include "props.h"
#include"room.h"
#include"object.h"
#include"player.h"
using namespace std;
props::props(string nam,string des,string ke,object* hidden,bool stat,room* cur)
{
    name=nam;
    desc=des;
    key=ke
    hidden_value=hidden;
    state=stat;
    cur->cur_props.push_back(this);
}
props::props(string nam ,string des,string ke ,object* hidden,bool stat)
{
    name=nam;
    desc=des;
    key=ke;
    hidden_value=hidden;
    state=stat;
}
bool props::act(agent* mons,bool flag)
{
    if(name==mons->getweapontokill())
    {
        cout<<"You can kill "<<mons->getname()<<" by typing it's lethal weapon name ( "<<mons->getweapontokill()<<" ). But be be careful you have only one chance."<<endl;
        string str;
        cin>>str;
        if(str==name)
        {
            cout<<mons->getname()<<" is dead !"<<endl;
            return true;
        }
    }
    return false;
}


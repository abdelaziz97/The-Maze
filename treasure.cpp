#include "treasure.h"
#include "object.h"
#include "room.h"
#include "player.h"
treasure::treasure(string nam,string des,string ke,object* hidden,bool stat,room* cur_room)
{
    name=nam;
    desc=des;
    key=ke;
    hidden_value=hidden;
    state=stat;
    cur_room->fixed_object.push_back(this);

}
bool treasure::act(agent* plyr,bool flag)
{

    for(int i=0; i<2 ; i++)
    {
        if(plyr->holding[i]!=NULL  &&  plyr->holding[i]->getname()==key)
        {
            cout<<"You can open the "<<this->getname()<<" by typing it's key name.(Hey,you there.Just type ( "<<key<<" .)"<<endl;
            string str;
            while(true)
            {
                cin>>str;
                if(str==key)
                {
                    cout<<"CONGRATULATIONS!!! YOU FOUND THE HIDDEN TREASURE. \n"<<endl;
                    break;
                }
                else
                {
                    cout<<"it is not the required key \n or (enter the object name again). \n"<<endl;
                }
            }
                return true;
        }

    }
    cout<<"Seems like you don't have the required object to get the treasure. \n"<<endl;
    return false;
}

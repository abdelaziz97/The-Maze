#include "fixedobject.h"
#include"room.h"
#include"player.h"
using namespace std;
fixedobject::fixedobject(string nam, string des, string ke,object* hidden,bool stat, room* cur)
{
    name=nam;
    desc=des;
    key=ke;
    hidden_value=hidden;
    state=stat;
    cur->fixed_object.push_back(this);

}
fixedobject::fixedobject(string nam, string des, string ke,object* hidden,bool stat)
{
    name=nam;
    desc=des;
    key=ke;
    hidden_value=hidden;
    state=stat;

}

bool fixedobject::act(agent* plyr,bool flag)
{
    if(flag)
    {
        if(this!=NULL)
        {
            if(key=="")
            {
                return true;
            }
            else
            {
                for(int i=0; i<2 ; i++)
                {
                    if(plyr->holding[i]!=NULL  &&  plyr->holding[i]->getname()==key)
                    {
                        cout<<"You can enter this room by typing the name of the required object.(Hey,you there.Just type "<<key<<".)"<<endl;
                        string str;
                        while(true)
                        {
                            cin>>str;
                            if(str==key)
                            {
                                cout<<"Now you can enter the room."<<endl;

                                break;
                            }
                            else
                            {
                                cout<<"It is not the required key \n or (enter the object name again)."<<endl<<endl;
                            }
                        }
                        return true;
                    }
                }
                cout<<"Seems like you don't have the required object to enter this room because of the "<<this->getname()<<"."<<"You need to get a "<<this->getkey()<<endl<<endl;
                return false;
            }
        }
    }
    else
    {

        if(key=="")
        {
            return true;
        }
        else
        {
            for(int i=0; i<2 ; i++)
            {
                if(plyr->holding[i]!=NULL  &&  plyr->holding[i]->getname()==key)
                {
                    cout<<"You can use/open "<<this->getname()<<" by typing it's key name. \n (Hey,you there.Just type (  "<<key<<"  .)"<<endl;
                    string str;
                    while(true)
                    {
                        cin>>str;
                        if(str==key)
                        {
                            cout<<"Now you can use/open the object."<<endl;
                            break;
                        }
                        else
                        {
                            cout<<"it is not the required key \n or (enter the object name again)."<<endl;
                        }
                    }
                    return true;
                }
            }
            cout<<"Seems like you don't have the required object to use/open this object."<<endl;
            return false;
        }
    }
    return true;
}

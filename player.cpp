#include "player.h"
#include"room.h"

player::player(string nam,string dis,string weap,room* cur)
{
    disc=dis;
    name=nam;
    weapontokill=weap;
    cur_room=cur;
    cur_room->enter(this);
    holding[0]=NULL;
    holding[1]=NULL;
}
bool player::act()
{

    string dir,choice;
    cout<<"You are in the "<<cur_room->getname()<<" ,"<<cur_room->getdesc()<<endl<<endl;
    cout<<"This is "<<name<<"'s turn.\n"<<endl;
    cur_room->printagents();
    cout<<endl<<"**********************************************************"<<"\n"<<endl;
    cur_room->printlinked();
    cout<<endl<<"**********************************************************"<<"\n"<<endl;
    cur_room->printfixedobjects();
    cout<<endl<<"**********************************************************"<<"\n"<<endl;
    cur_room->printprops();
    cout<<endl<<"**********************************************************"<<"\n"<<endl;
    bool check1;
    map<agent*,bool>::iterator it=cur_room->cur_monsters.begin();
    for(it ; it!=cur_room->cur_monsters.end() ; it++)
    {
        for(int i=0 ; i<2 ; i++)
        {
            if(this->holding[i]!=NULL)
            {
                bool ok=this->holding[i]->act(it->first,true);
                check1=ok;
                if(ok==true)
                {
                    break;
                }
            }
        }
        if(check1==false)
        {
            cout<<this->getname()<<", you are dead !"<<it->first->getname()<<" killed you."<<endl;
            return false;

        }
        else
        {
            cur_room->cur_monsters.erase(it);
            it--;
            map<agent*,bool>::iterator it2= cur_room->cur_agents.find(it->first);
            cur_room->cur_agents.erase(it2);
        }
    }
    while(true)
    {

        cout<<" (1)-if you want to get a prop from the room (if found). \n (2)-if you want to drop a prop. \n (3)-if you want to open/use a fixed object. \n (4)-if you want to view your inventory. \n (5)-if you want to go to a direction. "<<endl;
        cin>>choice;
        if(choice=="1")
        {
            getobject(cur_room);
        }
        else if(choice=="2")
        {
            dropobject(cur_room);
        }
        else if(choice=="3")
        {
            usefixedobject(cur_room);
            if(found_treasure)
                return true;
        }
        else if(choice=="4")
        {
            printholding();
        }
        else if(choice=="5")
        {
            cout<<endl<<"Which exit? or 'quit' : "<<endl;
            cin>>dir;
            if( (dir=="north" || dir=="south" || dir=="east" || dir=="west") && cur_room->getlinked(dir)!=NULL)
            {
                room *temp=cur_room->getlinked(dir);
                bool ok;
                if(temp->cur_object!=NULL)
                {
                    cout<< "You cannot enter this room without the required object"<<endl;
                    ok=temp->cur_object->act(this,true);
                    if(ok)
                    {
                        temp->cur_object=NULL;
                    }
                }
                bool check=false;
                if(ok || temp->cur_object==NULL)
                {
                    cur_room->leave(this);
                    cur_room=cur_room->getlinked(dir);
                    cout<<"you move to the "<<dir<<"."<<endl<<endl;
                    cur_room->enter(this);
                    cur_room->cur_object=NULL;
                    bool check1;
                    map<agent*,bool>::iterator it=cur_room->cur_monsters.begin();
                    for(it ; it!=cur_room->cur_monsters.end() ; it++)
                    {
                        for(int i=0 ; i<2 ; i++)
                        {
                            if(this->holding[i]!=NULL)
                            {
                                bool ok=this->holding[i]->act(it->first,true);
                                check1=ok;
                                if(ok==true)
                                {
                                    break;
                                }
                            }
                        }
                        if(check1==false)
                        {
                            cout<<this->getname()<<", you are dead !"<<it->first->getname()<<" killed you."<<endl;
                            return false;
                            //fe al game class ha3ml vector bl players w m3 kol return false hashel wa7ed w lw 5lso kolhom haktblo game over

                        }
                        else
                        {
                            cur_room->cur_monsters.erase(it);
                            it--;
                            map<agent*,bool>::iterator it2= cur_room->cur_agents.find(it->first);
                            cur_room->cur_agents.erase(it2);
                        }
                    }

                    cout<<"********************************"<<endl<<"*                              *"<<endl<<"*     NEXT PLAYER'S TURN.      *"<<endl<<"*                              *"<<endl<<"********************************"<<endl;
                    return true;
                }
            }
            else if(dir=="quit")
            {
                return false;
            }
            else if(dir!="north" && dir!="south" && dir!="east" && dir!="west")
            {
                cout<<"This is an invalid input. You still in the same room."<<endl<<endl;

            }
            else
            {
                cout<<"There's northing over there. You still in the same room."<<endl;
            }
        }
        else
        {
            cout<<"You have entered an invalid input."<<endl;
        }

    }
    return true;


}
void player::getobject(room* cur_room)
{
    string s;
    cout<<"Enter the name of the object you want: "<<endl;
    cin>>s;
    bool check=false,check1=false;
    vector<object*>::iterator it;
    for(it=cur_room->cur_props.begin(); it!=cur_room->cur_props.end(); it++)
    {
        if( (*it)->getname() == s)
        {
            for(int j=0 ; j<2 ; j++)
            {
                if(this->holding[j]==NULL)
                {
                    this->holding[j]=*it;
                    cur_room->cur_props.erase(it);
                    it--;
                    cout<<"Now you have this item."<<endl<<endl;
                    check=true;
                    break;
                }
            }
            check1=true;
        }
    }
    if(check1==false)
    {
        cout<<"You have entered a wrong name or this item is not available in this room."<<endl<<endl;
    }
    else if(check==false)
    {
        cout<<"Your inventory is full."<<endl;
    }
}
void player::dropobject(room* cur_room)
{
    string s;
    bool check=false;
    cout<<"Enter the name of the object you want to drop: ";
    cin >> s;
    for (int i=0 ; i<2 ; i++)
    {
        if(holding[i]!=NULL)
        {
            if(this->holding[i]->getname()==s)
            {
                cur_room->cur_props.push_back(this->holding[i]);
                this->holding[i]=NULL;
                cout<<"The item has been dropped successfully. \n"<<endl;
                check=true;
                break;
            }
        }
    }
    if(check==false)
    {
        cout<<"This item is not available. \n"<<endl;
    }
}
void player::usefixedobject(room* cur_room)
{
    cout<<"Enter the name of the fixed object you want to open/use: "<<endl;
    string str;
    cin>>str;
    for(int i=0 ; i<cur_room->fixed_object.size(); i++)
    {
        bool ok=cur_room->fixed_object[i]->act(this,false);
        if(ok && cur_room->fixed_object[i]->getstate()==true)
        {
            cout<<this->getname()<<", You win !!!"<<endl;
            found_treasure=true;
            break;
        }
        if(ok && cur_room->fixed_object[i]->getkey()!="")
        {
            cur_room->cur_props.push_back(cur_room->fixed_object[i]->gethiddenvalue());
            cout<<"There's a new prop in the room !!."<<cur_room->fixed_object[i]->gethiddenvalue()->getname()<<endl<<endl;
            cur_room->fixed_object.erase(cur_room->fixed_object.begin()+i);
            i--;
        }

    }
}
void player::printholding()
{
    bool check=false;
    cout<<"You have in your inventory......"<<endl;
    for(int i=0 ; i<2 ; i++)
    {
        if(holding[i]!=NULL)
        {
            check=true;
            cout<<holding[i]->getname()<<", "<<holding[i]->getdesc()<<endl;
        }
    }
    if(check==false)
    {
        cout<<"Nothing."<<endl;
    }
}

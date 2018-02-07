#ifndef AGENT_H
#define AGENT_H
#include<iostream>
#include "room.h"

using namespace std;
class room;
class object;

class agent
{
    protected:
        string name,disc,weapontokill;
        int nofrooms,current_nofrooms;
        room *holding_array[1000] = {};
    public:
        virtual bool act()=0;
        object **holding=new object*[2];
        bool found_treasure=false;
        bool type ;
        room *cur_room;
        string getname()
        {
            return name;
        }
        string getdisc()
        {
            return disc;
        }
        string getweapontokill()
        {
            return weapontokill;
        }
        arry_set(holding_array,NULL,sizeof holding_array);

};

#endif // AGENT_H

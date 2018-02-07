#include "monster.h"
#include"room.h"
#include<iostream>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include<vector>

class game;

monster :: monster(string nam,string dis,string weap, room* start)
{
    name=nam;
    disc=dis;
    weapontokill=weap;
    cur_room=start;
    cur_room->enter(this);
    cur_room->entermonster(this);
}
bool monster :: act()
{
    cur_room->leave(this);
    cur_room->leavemonster(this);

    this->AI(room* cur_room);

    cur_room->enter(this);
    cur_room->entermonster(this);


    return true;
}

int monster :: AI(room *current_room)
{
    queue<room* >queu_box;
    queu_box.push(current_room);
    room *holding_array[1000] = {};
    for (int x=0 ; x<1000 ; x++)
    {
        holding_array[i]=NULL;
    }
    nofrooms = 0 ;
    while(queu_box.size())
    {
        current_nofrooms=queu_box.size();
        while(current_nofrooms--)
        {
            room *r=queu_box.front();
            queu_box.pop();
            for(int i = 0 ; i < r->agents.size(); ++i)
            {
                if(r->agents[i]->checkthis()!=false)return nofrooms;

            }
            if(holding_array[r->n]!=NULL)continue;
            visited_array[r->n]=current_room;

            if(r->arr["east"]!=NULL)
                queu_box.push(r->arr["east"]);
            if(r->arr["west"]!=NULL)
                queu_box.push(r->arr["west"]);
            if(r->arr["south"]!=NULL)
                queu_box.push(r->arr["south"]);
            if(r->arr["north"]!=NULL)
                queu_box.push(r->arr["north"]);
        }
        nofrooms++;
    }
    return 1e9;
}

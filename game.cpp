#include"room.h"
#include"monster.h"
#include"player.h"
#include"agent.h"
#include"object.h"
#include"props.h"
#include"treasure.h"
#include "game.h"
#include <stdlib.h>
#include <time.h>
class fixedobject;
bool game::act()
{
    room start("the beginning of your adventurous trip","You are entering the WOODS."),
         cotton ("Cottonwood creek","BECAREFUL it's your first steps "),
         garden ("The beauty of nature ","There are the beautiful different kinds of flowers"),
         twoforks ("two forks lookout","LOOKOUT!! Monsters over there !!"),
         southern("Southern seas","The sea looks so dangerous and the waves looks furious"),
         northern ("Northern seas","You are in one of the most important stages"),
         cave ("Horrible cave","It sounds horrible , Watch out"),
         underwater ("Underwater cave","I think it is not peaceful there !"),
         secret ("Secret pit","You are safe right here"),
         thunder("Thunder canyon","It is not comfortable in this place"),
         wapiti ("Wapiti meador ","You must search for the best you can get from there !"),
         middle_woods ("Middle woods","You are in the middle of the JUNGLE"),
         blackwood ("Black wood woods","Enjoy the beauty there !");



    start.link(&cotton,"north");
    cotton.link(&garden,"east");
    cotton.link(&wapiti,"west");
    cotton.link(&middle_woods,"north");
    cotton.link(&start,"south");
    garden.link(&cotton,"west");
    garden.link(&twoforks,"east");
    twoforks.link(&garden,"west");
    twoforks.link(&southern,"north");
    southern.link(&twoforks,"south");
    southern.link(&middle_woods,"west");
    southern.link(&northern,"north");
    northern.link(&cave,"east");
    northern.link(&blackwood,"west");
    northern.link(&southern,"south");
    northern.link(&underwater,"north");
    cave.link(&northern,"west");
    wapiti.link(&thunder,"north");
    wapiti.link(&cotton,"east");
    thunder.link(&wapiti,"south");
    thunder.link(&secret,"north");
    thunder.link(&blackwood,"east");
    middle_woods.link(&southern,"east");
    middle_woods.link(&blackwood,"north");
    middle_woods.link(&cotton,"south");
    blackwood.link(&northern,"east");
    blackwood.link(&thunder,"west");
    blackwood.link(&middle_woods,"south");
    secret.link(&thunder,"south");
    underwater.link(&northern,"south");

    player *player1=new player("Mable","a young girl from an unknown town","",&start),*player2=new player("Dipper","Mable's twin brother","",&start);
    monster *monster1=new monster("Master_Ludo","a young evil peacock.","wand",&twoforks),*monster2=new monster("Bill_Cipher","a triangular devil form another dimension." ,"dimensional_gun",&cave);
    monster *monster3=new monster("Afrit","Arabic fire spirit","spell",&thunder);

    player1.type=true;
    player2.type=true;
    monster1.type=false;
    monster2.type=false;
    monster3.type=false;

    vector<agent*> agents;
    vector<agent*> players;

    agents.push_back(player1);agents.push_back(player2);agents.push_back(monster1);agents.push_back(monster2);agents.push_back(monster3);
    players.push_back(player1);players.push_back(player2);

    props *prop1=new props("wand","It kills Master Ludo.","",NULL,false,&wapiti);
    props *prop2=new props("dimensional_gun","It kills Bill Cipher.","",NULL,false,&cotton);
    props *prop3=new props("secret_key","You need it to get the treasure ","",NULL,false);
    props *prop4=new props("magic_sword","It opens the Box","",NULL,false);
    props *prop6=new props("Magic_stick","It opens the magic safe","",NULL,false,&cotton);
    props *prop7=new props("spell","It kills the Afrit","",NULL,false);
    fixedobject *fixed1=new fixedobject("box","try to open","magic_sword",prop3,false,&middle_woods);
    fixedobject *fixed3=new fixedobject("Magic_safe","Open it","Magic_stick",prop4,false,&wapiti);
    fixedobject *fixed2=new fixedobject("wall","try to breakthrough","Magic_stick",NULL,false);
    fixedobject *fixed5=new fixedobject("obstacle","try to pass","secret_key",NULL,false)
    fixedobject *fixed4=new fixedobject("Spell_Factory","Get the spell you want to complete your journey","",prop7,false,&garden);
    wapiti.cur_object=fixed2;
    middle_woods.cur_object=fixed5;
    treasure *treasures=new treasure("treasure","the end","secret_key",NULL,true,&underwater);
    while(true)
    {
        for(int i=0;  i<agents.size()  ; i++)
        {
            bool ok = agents[i]->act();
            if(ok && agents[i]->getweapontokill()=="" && agents[i]->cur_room==&secret)
            {
                cout<<"WOW, seems like you found a magical portal it would take you somewhere magical...or just a random room."<<endl;
                cout<<"if you want to enter the portal type go,else type anything else."<<endl;
                string str;
                cin>>str;
                if(str=="go")
                {
                    int n = rand() % 8;
                    bool check1;
                    room* rooms[8]= {&wapiti,&thunder,&cave,&northern,&garden,&blackwood,&start,&southern};
                    agents[i]->cur_room=rooms[n];
                    cout<<"You have moved to "<<agents[i]->cur_room->getname()<<endl;
                    map<agent*,bool>::iterator it=agents[i]->cur_room->cur_monsters.begin();
                    for(it ; it!=agents[i]->cur_room->cur_monsters.end() ; it++)
                    {
                        for(int i=0 ; i<2 ; i++)
                        {
                            if(agents[i]->holding[i]!=NULL)
                            {
                                bool ok=agents[i]->holding[i]->act(it->first,true);
                                check1=ok;
                                if(ok==true)
                                {
                                    break;
                                }
                            }
                        }
                        if(check1==false)
                        {
                            cout<<agents[i]->getname()<<", you are dead !"<<it->first->getname()<<" killed you."<<endl;
                            return true;

                        }
                        else
                        {
                            agents[i]->cur_room->cur_monsters.erase(it);
                            it--;
                            map<agent*,bool>::iterator it2=agents[i]->cur_room->cur_agents.find(it->first);
                            agents[i]->cur_room->cur_agents.erase(it2);
                        }
                    }


                }
            }
            else if(ok && agents[i]->found_treasure)
            {
                cout<<"Game is over !!"<<endl;
                return true;
            }
            else if(!ok)
            {
                for(int j=0 ; j<players.size(); j++)
                {
                    if(players[j]==agents[i])
                    {
                        players.erase(players.begin()+j);
                        break;
                    }
                }
                agents.erase(agents.begin()+i);
                if(players.size()==0)
                {
                    cout<<"Game Quits."<<endl;
                    return false;
                }
            }
        }
    }

    return true;


}

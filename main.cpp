#include <iostream>
#include <stdlib.h>
#include <time.h>
#include"game.h"
#include <queue>
#include<vector>
using namespace std;

int main()
{
    srand(time(NULL));
    game newgame;

    while(true)
    {
        string str;
        cout<<"To start a new game type 1 , To quit the program type 2 , to view the instructions type 3. "<<endl;
        cin>>str;
        if(str=="1")
        {
            string s;
            cout<<"Welcome to gravity falls, once upon a time two little kids named Mable and Dipper got lost in the woods (i dunno why but the game goes like this, so you got NO OTHER OPTION!!!) and they need your help to guide them out of there by finding the treasure."<<endl;
            cout<<"press anything to continue....."<<endl;
            cin>>s;
            cout<<"I know that getting lost in the woods has nothing to do with finding the treasure and that i'm horrible at story telling but please try to keep up with me. THANKS :D. "<<endl;
            cout<<"press anything to continue....."<<endl;
            cin>>s;
            cout<<"uhm, Ok no more talking lets play."<<endl;
            cout<<"press anything to continue....."<<endl;
            cin>>s;
            newgame.act();
        }
        else if(str=="2")
        {
            return 0;
        }
        else if(str=="3")
        {
            cout<<"Just try not to die.....oh and find the treasure ! "<<endl;
        }
    }
}

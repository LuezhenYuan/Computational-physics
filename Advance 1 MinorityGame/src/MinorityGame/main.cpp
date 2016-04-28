//This program implement Minority Game, a microscopic modeling markets.
//This program supports mixed model. In other word, there can be many types of agents,
//  each type have their own s, and m.

//////
//Three classes is designed: Game, agent, history.
//When the program starts, a Game object is instantiated, and it initializes a
//  given number of agent objects and a history object. When the Game::BatchRun
//  or Game::Run method is called, the minority game model starts running. A agent object
//  get history record from the history object, and makes decision. She sends the decision
//  to the Game object, and the latter judges which side wins. The Game object send this
//  message to the history object and all the agent objects, and they update their states.
//  Till now, single game is finished, and the minority game steps to a next cycle.
//  A minority game often runs 10000 cycles, and after that, the game stops, and
//  the program comes to an end.
///////

////
//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//Compile command: $ g++ -std=c++11 *.cpp -o MG.out
//To run the program, just $ ./MG.out
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////

////
//Author: Luezhen Yuan
//Last update: 20160403
//Add comments: 20160424
/////////////////////////////////////////////
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <map>
#include "Game.h"
#include "agent.h"
#include "history.h"
using namespace std;

int main()
{
    /*
    //test 'history' class
    history his(5);
    cout<<(int)his[0]<<'-'<<(int)his[1]<<'-'<<(int)his[2]<<'-'<<(int)his[3]<<'-'<<(int)his[4]<<"\n";
    his.PushPop(1);his.PushPop(0);
    cout<<(int)his[0]<<'-'<<(int)his[1]<<'-'<<(int)his[2]<<'-'<<(int)his[3]<<'-'<<(int)his[4]<<"\n";

    //test 'agent' class
    agent agent1(3,5);//history size is 5, 3 strategies.
    cout<<"Decision: "<<(int)agent1.decide(his)<<endl;
    char ch=1;
    agent1.update_strategy(ch);
    */
    pair<int,int> pa;
    int ind,i;
    int time_steps,Individual_run;
    map<pair<int,int>,int> S;
    int s,m,N;
    int ex;
    cout<<"Minority Game\n";
    while(1){
        i=0;
        while(1){
            cout<<++i<<"th type of agents:\n";
            cout<<"s strategies hold for one agent(in this type). [5]:";cin>>s;
            cout<<"\nm size of memory used by one agent(in this type). [3]:";cin>>m;
            cout<<"\nNumber of agents(in this type). [101]:";cin>>N;
            pa.first=s;pa.second=m;
            S[pa]=N;
            cout<<"\n1 for entering next type of agent;-1 for finishing the entry.:";cin>>ind;
            cout<<"\n";
            if(ind==-1)break;
        }
        Game game(S);

        cout<<"\nHow many time steps in one run? [10000]:";cin>>time_steps;
        cout<<"\nHow many individual run? [32]:";cin>>Individual_run;
        game.BatchRun("result",Individual_run,time_steps);
        cout<<"\nFinished\n\n";
        cout<<"\n1 for a new game;-1 for exit. [-1]:";cin>>ex;
        if(ex==-1) break;
        cout<<"--------\n\n";
    }
    cout<<"\nFinished Minority Game!\nGoodBye!\n";

    return 0;
}

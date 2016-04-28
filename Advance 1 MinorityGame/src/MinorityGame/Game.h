#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <map>
#include "agent.h"
#include "history.h"
#include <iterator>
#include <utility>
#include <string>
#include <fstream>
using namespace std;
class Game{
map<pair<int,int>,int> m_S;
agent** m_agents;
history* p_hist;
int m_N;
public:
Game(map<pair<int,int>,int> S);//Initialize N agents. use new and delete[]
~Game();
void Run(string file_name,int time_steps=10000);//Runing the minority game model for time_steps cycles.
void BatchRun(string file_name,int Individual_run=32,int time_steps=10000);
};

#endif // GAME_H_INCLUDED

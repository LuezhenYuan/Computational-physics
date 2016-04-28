#ifndef AGENT_H_INCLUDED
#define AGENT_H_INCLUDED
#include <stdlib.h>
#include <cmath>
#include "history.h"
using namespace std;
class agent{
int m_s;//number of strategies hold for one agent
int m_m;//size of history used by one agent
char* m_strategy_bag;//store all m_s strategies of one agent
int* m_strategy_scores;//store the score on each strategies
int m_ind;//store the history used for choosing strategies and making decision. the name m_ind
// means history's index in m_strategy_bag
public:
agent(int s,int m);
~agent(){free(m_strategy_bag);free(m_strategy_scores);}
const char decide(const history& hist);//Make decision based on the history record.
void update_strategy(const char& success);//In:succeed side '0' or '1'.
void reset();//reset strategies in the strategy bag(). Game::Batchrun will call this method.
// This method helps to save memory allocation task. Without this method, Game::Batchrun will
// delete the current agent, and initialize a new one for the next Individual_run.
};




#endif // AGENT_H_INCLUDED

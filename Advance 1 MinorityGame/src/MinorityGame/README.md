# Key variables
Varaible | comments
---------|---------
m        |memory(used for decision). There are 2^m histories, so there are 2^{2^m} strategies. When m= 5, 2^m= 32, 2{2^m}= 2^32= 4294967296. The latter number is really large even m seems small!
s        |c
N        |number of agents
# Special cases
Ties between strategies are decided by a coin toss.
We must also create a short (of order m) random history of 0’s and 1’s, so that the strategies can be initially evaluated.

# data structure
Histroy | queue(array with a head indicator)

class history{
private:
char* m_arr;
int m_head;
int m_size;
publish:
history(int size):m_arr(NULL),m_size(size),m_head(0){m_arr=(char*)malloc(sizeof(char)*m_size);}
~history(){free(m_arr);}
void PushPop();
const char* read();
};

Agent

class agent{
int m_s;
int m_m;
char* m_strategy_bag;
int* m_strategy_scores;
public:
agent(int s,int m):m_s(s),m_m(m),m_strategy_bag(NULL){m_strategy_bag=(char*)malloc(sizeof(char)*exp2(m)*s );}
~agent(){free(m_strategy_bag);}
char decide(const char* history);
void update_strategy(char success);//In:succeed side '0' or '1'.
void reset();//reset strategies in the strategy bag().
};

//How to match history to strategy?
//sum(exp2(i) * history[i]) is the index in one strategy array.
Game

class Game{
map<int,int> m_S;
agent* m_agents;
public:
Game(map<int,int> S):m_S(S);//Initialize N agents. use new and delete[]
void Run(int time_steps=10000);
void BatchRun(int Individual_run=32,int time_steps=10000);
};

# Feature of my program
1. support Mixed Model(for many types of agents)
2. Each type of agents have their own sucessful rate and zero side ratio.

```{bash}
paste -d '\t' result_SucceedRatio*>SucceedRatio.txt
paste -d '\t' result_ZeroRatio*>ZeroRatio.txt

```

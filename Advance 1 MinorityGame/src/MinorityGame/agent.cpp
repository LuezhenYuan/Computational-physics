#include "agent.h"
#include <random>
agent::agent(int s,int m):m_s(s),m_m(m),m_strategy_bag(NULL){
    m_strategy_bag=(char*)malloc(sizeof(char)*exp2(m)*s );
    m_strategy_scores=(int*)malloc(sizeof(int)*m_s );

    std::random_device rd;
    std::mt19937_64 rseed(rd());
    std::uniform_int_distribution<int> dr(0,1);
    //srand((unsigned) time(NULL));
    for(int i=0;i<exp2(m)*s;i++){
        m_strategy_bag[i]=(char)dr(rseed);

        //m_strategy_bag[i]=(char)(rand()%2);
        //cout<<(int)m_strategy_bag[i]<<"-";
    }
    //cout<<"\n";
    for(int i=0;i<m_s;i++) m_strategy_scores[i]=0;
}
const char agent::decide(const history& hist){
    m_ind=0;
    for(int i=m_m-1;i>=0;i--){
        m_ind=m_ind*2+hist[i];
    }
    int* maxindex;
    maxindex=(int*)malloc(sizeof(int)*m_s);
    int n_max=0,max_score=0;
    for(int i=0;i<m_s;i++){
        if(m_strategy_scores[i]>max_score){
            max_score=m_strategy_scores[i];
            n_max=1;
            maxindex[n_max-1]=i;
        }
        else if(m_strategy_scores[i]==max_score){
            maxindex[n_max++]=i;
        }
        else continue;
    }
    std::random_device rd;
    std::mt19937_64 rseed(rd());
    std::uniform_int_distribution<int> dr(0,n_max-1);
    //srand((unsigned) time(NULL));
    if(n_max>1){
        maxindex[0]=maxindex[dr(rseed)];
    }

    return m_strategy_bag[m_ind+(int)exp2(maxindex[0])];
}

void agent::update_strategy(const char& success){
    for(int i=0;i<m_s;i++){
        //cout<<(int)m_strategy_bag[m_ind+(int)exp2(i)]<<'-'<<(int)success<<endl;
        if(m_strategy_bag[m_ind+(int)exp2(i)]==success)
            m_strategy_scores[i]++;
        //cout<<m_strategy_scores[i]<<endl;
    }
}

void agent::reset(){
    std::random_device rd;
    std::mt19937_64 rseed(rd());
    std::uniform_int_distribution<int> dr(0,1);
    //srand((unsigned) time(NULL));
    for(int i=0;i<exp2(m_m)*m_s;i++){
        m_strategy_bag[i]=(char)dr(rseed);
    }
}

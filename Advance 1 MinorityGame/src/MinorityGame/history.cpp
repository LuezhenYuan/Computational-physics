#include "history.h"
//#include <time.h>
#include <random>
history::history(int size):m_arr(NULL),m_size(size),m_head(0){
    m_arr=(char*)malloc(sizeof(char)*m_size);
    std::random_device rd;
    std::mt19937_64 rseed(rd());
    std::uniform_int_distribution<int> dr(0,1);
    //srand((unsigned) time(NULL));
    for(int i=0;i<m_size;i++){
        m_arr[i]=dr(rseed);

        //m_arr[i]=(char)(rand()%2);
        //cout<<(int)m_arr[i]<<endl;
    }
}

void history::PushPop(char success){
m_arr[m_head]=success;
m_head=m_head+1<m_size?m_head+1:0;
}
const char history::operator[](int index)const{
int ind = m_head-index-1;
if(ind<0) ind+=m_size;
if(ind<0 || ind>m_size) {cout<<"Error in history::operator[]\n";return -1;}
else return m_arr[ind];
}

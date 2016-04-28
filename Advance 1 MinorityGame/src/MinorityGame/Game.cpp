# include "Game.h"

Game::Game(map<pair<int,int>,int> S):m_S(S),p_hist(NULL){
    m_N=0;
    for(std::map<pair<int,int>,int>::iterator iter=m_S.begin();iter!=m_S.end();iter++){
        m_N+=iter->second;
    }
    if(m_N%2!=1){
        cout<<"The number of agents should be odd!\nSet N to N+1.\n";
        m_N++;
    }
    m_agents=(agent**)malloc(sizeof(agent*)*m_N);
    int i=0;
    int largest_memory=0;
    for(std::map<pair<int,int>,int>::iterator iter=m_S.begin();iter!=m_S.end();iter++){
        for(int j=0;j<iter->second;j++)
            m_agents[i++]=new agent( (iter->first).first,(iter->first).second);
        if((iter->first).second>largest_memory) largest_memory=(iter->first).second;
    }

    p_hist=new history(largest_memory);
}

Game::~Game(){
    for(int i=0;i<m_N;i++)
        delete m_agents[i];
    free(m_agents);
    delete p_hist;
}

void Game::Run(string file_name,int time_steps){
    ofstream out1(file_name+"_SucceedHistory.txt",ios::app);
    ofstream out2(file_name+"_ZeroRatio.txt",ios::app);
    ofstream out3(file_name+"_SucceedRatio.txt",ios::app);
    ofstream out4;
    out1<<"#Succeed History Record\n";
    out2<<"#Zero side Ratio\n";
    out3<<"#Succeed Ratio\n";
    int succsess_side;int i,k;
    int*zero_side;
    char ch;
    zero_side=(int*)malloc(sizeof(int)* (m_S.size()) );
    //Start for out4
    for(i=0;i<m_S.size();i++){
        ch=i +'0';
        out4.open(file_name+"_ZeroRatio_"+ch+".txt",ios::app);
        out4<<"#Type "<<i<<"th agents' Zero Side Ratio\n";
        out4.close();out4.clear();
        out4.open(file_name+"_SucceedRatio_"+ch+".txt",ios::app);
        out4<<"#Type "<<i<<"th agents' Succeed Ratio\n";
        out4.close();out4.clear();
    }
    for(int j=0;j<time_steps;j++){
        /*//Version 1:
        succsess_side=0;
        for(i=0;i<m_N;i++){
            succsess_side+=m_agents[i]->decide(*p_hist);
        }
        */
        //Version 2:
        i=0;k=0;
        succsess_side=0;
        for(std::map<pair<int,int>,int>::iterator iter=m_S.begin();iter!=m_S.end();iter++){
            zero_side[i]=0;
            ch=i +'0';
            out4.open(file_name+"_ZeroRatio_"+ch+".txt",ios::app);
            for(int j=0;j<iter->second;j++)
                zero_side[i]+=m_agents[k++]->decide(*p_hist);
            succsess_side+=zero_side[i];
            zero_side[i]=iter->second-zero_side[i];
            out4<<zero_side[i]*1.0/iter->second<<endl;
            out4.close();out4.clear();
            i++;
        }
        //Version 2 finished.

        //cout<<succsess_side<<endl;
        out2<<(m_N-succsess_side)*1.0/m_N<<endl;
        out3<<( (succsess_side>m_N/2)?( (m_N-succsess_side)*1.0/m_N ):( succsess_side*1.0/m_N ) ) <<endl;
        succsess_side=(succsess_side>m_N/2)?0:1;

        // output successful rate of each type of agent
        i=0;
        for(std::map<pair<int,int>,int>::iterator iter=m_S.begin();iter!=m_S.end();iter++){
            ch=i +'0';
            out4.open(file_name+"_SucceedRatio_"+ch+".txt",ios::app);
            if(succsess_side==0){
                out4<<zero_side[i]*1.0/iter->second<<endl;
            }
            else{
                out4<<(iter->second -zero_side[i])*1.0/iter->second<<endl;
            }
            out4.close();out4.clear();
            i++;
        }

        //
        out1<<succsess_side<<endl;
        for(i=0;i<m_N;i++){
            m_agents[i]->update_strategy(succsess_side);


        }
        p_hist->PushPop(succsess_side);
    }
    //End for out4
    for(i=0;i<m_S.size();i++){
        ch=i +'0';
        out4.open(file_name+"_ZeroRatio_"+ch+".txt",ios::app);
        out4<<"\n\n";
        out4.close();out4.clear();
        out4.open(file_name+"_SucceedRatio_"+ch+".txt",ios::app);
        out4<<"\n\n";
        out4.close();out4.clear();
    }

    out1<<"\n\n";out2<<"\n\n";out3<<"\n\n";
    out1.close();out1.clear();
    out2.close();out2.clear();
    out3.close();out3.clear();
}

void Game::BatchRun(string file_name,int Individual_run,int time_steps){
    Run(file_name,time_steps);
    for(int i=1;i<Individual_run;i++){
        for(int i=0;i<m_N;i++)
            m_agents[i]->reset();
        Run(file_name,time_steps);

    }
}

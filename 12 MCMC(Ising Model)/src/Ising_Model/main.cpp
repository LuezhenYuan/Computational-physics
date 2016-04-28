//This program use Metropolis's MCMC method to simulate the Ising model.

////
//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//Compile command: $ g++ -std=c++11 main.cpp -o Ising.out
//To run the program, just $ ./Ising.out
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////

////
//Author: Luezhen Yuan
//Last update: 20160422
/////////////////////////////////////////////

//The lattice point
#define N 50
#define M 50
//$H=-J\sum\limits_{<i,j>}s_is_j$
#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
using namespace std;
void Importance_Sampling_on_Ising_Model(double J_kBT,int MCS_Max,string file);
int main()
{
    cout << "Ising model." << endl;
    double J_KBT;
    cout<<"J/k_B T [0.55]:";cin>>J_KBT;
    int MCS_Max;
    cout<<"How many Monte Carlo steps in one configuration? [10000]:";cin>>MCS_Max;
    int times;
    cout<<"How many configurations runs? [1000]:";cin>>times;
    string file="result";
    for(int i=0;i<times;i++)
        Importance_Sampling_on_Ising_Model(J_KBT,MCS_Max,file+"_"+to_string(J_KBT)+"_"+to_string(i)+".txt");
    return 0;
}

void Importance_Sampling_on_Ising_Model(double J_kBT,int MCS_Max,string file){//J_kBT is $J/K_B T$
    double tau[3]={exp(-4*J_kBT),exp(-8*J_kBT),1};
    int state[N*M];
    std::random_device rd;
    std::mt19937_64 rseed(rd());
    std::uniform_real_distribution<double> dr(0,1);
    //Initial state
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            state[M*i+j]=dr(rseed)<0.5?-1:1;
        }
    }
    int t;//simulated time step
    int t_MCS;//Monte Carlo time step
    int k;
    int tmp;
    double sum;
    ofstream out(file);
    out<<"#m\n";
    for(t_MCS=0;t_MCS<MCS_Max;t_MCS++){
        for(t=0;t<N*M;t++){
            k=int(dr(rseed)*N*M);//The kth lattice point(k/M row, k%M column, indexed from 0)
            tmp=state[k]*(state[k+1>=N*M?0:k+1]+state[k-1<0?N*M-1:k-1]+state[k+M>=N*M?k+M-M*N:k+M]+state[k-M<0?k-M+M*N:k-M]);
            //cout<<tmp<<',';
            if(tmp<=0){
                //tau[2] case
                state[k]*=-1;
            }
            else if(tmp==2){
                //tau[0] case
                if(dr(rseed)<tau[0])state[k]*=-1;
            }
            else if(tmp==4){
                //tau[1] case
                if(dr(rseed)<tau[1])state[k]*=-1;
            }
        }
        sum=0;
        for(k=0;k<N*M;k++){
            sum+=state[k];
        }
        sum/=N*M;
        out<<abs(sum)<<endl;
    }
    out<<"\n\n";
    out.close();out.clear();
}

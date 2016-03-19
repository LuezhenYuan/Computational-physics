//This program is a practice in basic statistic analysis of data

/////////////////
//Constrain for parameter:
//N无,n>=1000较好,s>=10(不宜过小)
/////////////////
//# 程序流程
//1. 产生随机数,形成数据集(输入N,n,输出data,并输出到文件out(文件名str,str_dataset.txt))
//2. 画直方图(输入data,s,输出频数表str_freqtab.txt)
//3. 计算基本统计量(输入data,输出平均值avera,平均值的标准偏差avestandevia)
//4. 错误值剔除(输入data,输出原始data到文件中(可选),data变量原处修改)
////////////////

//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//!!!!!注意：需要编译器开启支持c++11标准的选项！
//!!!!!Attention: Have your compiler follow the c++11 ISO C++ language standard [-std=c++11]
//!!!!!You can modify your "Global compiler settings": find the "c++11" like term and allow it!
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////

//Author: Luezhen Yuan
//Last update: 20160313
/////////////////////////////////////////////
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class SimpleStatisticsProject{
private:
    int m_N,m_n;
    vector<double> m_data;
    ofstream m_out;
    string m_str;
    int m_s;
    double avera,avestandevia;
public:
    SimpleStatisticsProject():m_N(3),m_n(1000),m_data(),m_out(),m_str("result"),m_s(10),avera(0),avestandevia(0){}
    SimpleStatisticsProject(int N,int n,string str,int s):m_N(N),m_n(n),m_data(m_n),m_out(),m_str(str),m_s(s),avera(0),avestandevia(0){}
    ~SimpleStatisticsProject(){}
    void Dataset(int N,int n, string str);//Generate dataset through random numbers. When you want N change and generate new dataset, just call this function!

    void Histogram(int s=10);//get frequancy table
    void Statistic();//calculate average, standard deviation fo average
    void ChangeParameter(int n,int s,string str){m_n=n;m_s=s;m_str=str;}
    void PautaFilter();//pauta criterion
};


int main()
{
    int i=0,N=0,n=0,s=0;
    int low=1,high=50;
    string str;
    cout<<"Simulation for Simple Statistics\n";
    cout<<"n:";cin>>n;
    cout<<"s:";cin>>s;
    cout<<"Output file name:";cin>>str;
    SimpleStatisticsProject sim(N,n,str,s);//call initiator
    while(1){
        cout<<"\nSimulation for Simple Statistics\n";
        cout<<"0-Exit\n"<<"1-Simulation for one N\n"<<"2-Simulation for a batch of Ns\n"<<"3-Change parameter\n";
        cout<<"------\nYour choose:";cin>>i;
        if(i==1){
            cout<<"N:";cin>>N;//calculate for one N
            sim.Dataset(N,n,str);
            sim.Histogram();
            sim.Statistic();
            sim.PautaFilter();
            sim.Histogram();
            sim.Statistic();
            cout<<"Simulation done!\n";
        }
        else if(i==2){//calculate for many Ns
            cout<<"Lower bound of N(included):";cin>>low;
            cout<<"Higer bound of N(included):";cin>>high;
            if(low<1){
                cout<<"Lower bound should larger than 0\n";
                continue;
            }

            for(int i=low;i<=high;i++){
                sim.Dataset(i,n,str);
                sim.Statistic();
            }
            cout<<"Simulation done!\n";
        }
        else if(i==3){
            cout<<"n:";cin>>n;
            cout<<"s:";cin>>s;
            cout<<"Output file name:";cin>>str;
            sim.ChangeParameter(n,s,str);
            cout<<"Change!\n";
        }
        else break;
    }
    cout<<"Exit\n";
    return 0;
}


void SimpleStatisticsProject::Dataset(int N,int n,string str){
    m_n=n;
    m_data.clear();
    m_data.resize(m_n);
    m_str=str;
    m_N=N;
    int i=0,j=0;
    double tmp;

    //Random number generator engine
    std::random_device rd;
    std::mt19937_64 rseed(rd());
    //Random distribution`
    std::uniform_real_distribution<double> dr(0,1);//From 0 to 1

    //store the dataset to file
    m_out.open(m_str+"_dataset.txt",ios::app);
    m_out<<"#Dataset\n";
    m_out<<"#N:"<<m_N<<",n:"<<m_n<<"\n";

    for(i=0;i<m_n;i++){
        tmp=0;
        for(j=0;j<m_N;j++){
            tmp+=dr(rseed);

        }
        tmp/=m_N;
        m_data[i]=tmp;
        m_out<<tmp<<"\n";
    }
    m_out<<"\n\n";
    m_out.close();
    m_out.clear();
    //cout<<"Successful construct data set!\n";
}

void SimpleStatisticsProject::Histogram(int s){
    m_s = s;
    m_n=m_data.size();
    vector<int> freq(s);

    //set all elements to 0
    for(vector<int>::iterator iter=freq.begin();iter!=freq.end();iter++) *iter=0;
    for(int i=0;i<m_n;i++)
        freq[int(m_data[i]*s)]++;

    m_out.open(m_str+"_freqtable.txt",ios::app);
    m_out<<"#Dataset\n";
    m_out<<"#N:"<<m_N<<",n:"<<m_n<<",s:"<<s<<"\n";
    for(int i=0;i<s;i++){
        m_out<<i*1.0/s+1.0/s/2<<"\t"<<1.0*freq[i]/m_n<<"\n";
    }
    m_out<<"\n\n";
    m_out.close();
    m_out.clear();
}

void SimpleStatisticsProject::Statistic(){
    m_n=m_data.size();
    avera=0,avestandevia=0;
    for(int i=0;i<m_n;i++){
        avera+=m_data[i];
        avestandevia+=m_data[i]*m_data[i];
    }
    avera/=m_n;//average
    avestandevia = sqrt( (avestandevia/m_n-avera*avera) / (m_n-1) );//standard deviation of average

    m_out.open(m_str+"_stat.txt",ios::app);
    m_out<<"#Dataset\n";
    m_out<<"#N:"<<m_N<<",n:"<<m_n<<",s:"<<m_s<<"\n";

    m_out<<"average\t"<<avera<<endl;
    m_out<<"average standard deviation\t"<<avestandevia<<endl;
    m_out<<"\n\n";
    m_out.close();
    m_out.clear();
}

void SimpleStatisticsProject::PautaFilter(){
    std::vector<double> store;
    for(int i=0;i<m_n;i++){
        if(m_data[i]<avera-3*avestandevia*sqrt(m_n) || m_data[i]>avera+3*avestandevia*sqrt(m_n)) continue;//Use Pauta method to filter wrong points
        store.push_back(m_data[i]);
    }
    m_n = store.size();
    m_data.clear();
    m_data = store;
    m_str=m_str+"_filter";
    //print infomation
    m_out.open(m_str+"_dataset.txt",ios::app);
    m_out<<"#Dataset\n";
    m_out<<"#N:"<<m_N<<",n:"<<m_n<<"\n";

    for(int i=0;i<m_n;i++){
        m_out<<m_data[i]<<endl;
    }
    m_out<<"\n\n";
    m_out.close();
    m_out.clear();

}

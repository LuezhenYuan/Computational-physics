//This program implement two 'Smoothing' methods:
//1)five points unweighted sliding-average smooth(五点线性平滑)
//2)five points weighted sliding-average smooth(cubic)(五点三次加权平滑)
/////////

//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//!!!!!注意：需要编译器开启支持c++11标准的选项！
//!!!!!Attention: Have your compiler follow the c++11 ISO C++ language standard [-std=c++11]
//!!!!!You can modify your "Global compiler settings": find the "c++11" like term and allow it!
//Compile command: $ g++ -std=c++11 main.cpp SimpleStatisticsProject.cpp -o a.out
//To run the program, just $ ./a.out
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////

//Author: Luezhen Yuan
//Last update: 20160402
/////////////////////////////////////////////
#include <iostream>
#include <string>
#include "SimpleStatisticsProject.h"
#include <fstream>
using namespace std;

class smoothing{
private:
    SimpleStatisticsProject data;//SimpleStatisticsProject is a previously constructed class, and here it is used to generate datasets.
    int m_n;// number of running for one N. this parameter is used in SimpleStatisticsProject object.
    string m_str;// data file name
    double*y;// data stored in this 'vector'
    int m_high,m_low;// N range form m_low to m_high
    int m_havedata;// m_havedata=1 means the object(实例化的对象) already called smoothing::datagenerated() method, and y contains data.
    void method1();// five points unweighted sliding-average smooth(五点线性平滑)
    void method2();// five points weighted sliding-average smooth(cubic)(五点三次加权平滑)
public:
    smoothing(int n,string filename):data(1,n,filename,1),m_n(n),m_str(filename),y(NULL),m_havedata(-1){}
    ~smoothing(){free(y);}
    void datagenerate(int low,int high);// Generate standard deviation for average~N
    void smooth(int method);// method=1: unweighted sliding-average method;method=2: weighted cubic sliding-average method.
    int havedata(){return m_havedata;}
};

int main()
{
    int n=1000,low=1,high=50,ind=1,ex=-1,newdata;
    cout<<"Data smoothing\n";
    string str;//file name
    cout<<"File name:";cin>>str;
    cout<<"n [1000]:";cin>>n;
    smoothing sim(n,str);
    while(1){
        if(sim.havedata()==1){
            cout<<"Generate new dataset? (1 yes,-1 no) [-1]:";cin>>newdata;
            if(newdata!=-1){
                cout<<"Low case for N [1]:";cin>>low;
                cout<<"High case for N [50]:";cin>>high;
                if(low>=high) continue;
                sim.datagenerate(low,high);
            }
        }
        else{
        cout<<"Low case for N [1]:";cin>>low;
        cout<<"High case for N [50]:";cin>>high;
        if(low>=high) continue;
        sim.datagenerate(low,high);//Here generate dataset
        }

        cout<<"Smoothing methods:\n";//Two models
        cout<<"1: unweighted sliding-average smoothing(five points)\n";
        cout<<"2: weighted(cubic) sliding-average smoothing(five points)\n";
        cout<<"Choose smoothing method [1]:";cin>>ind;
        sim.smooth(ind);
        cout<<"Finished!\n\n";
        cout<<"Exit:-1, continue:1 [-1]:";cin>>ex;
        if(ex==-1) break;
    }

    return 0;
}

void smoothing::datagenerate(int low,int high){
    m_low=low;m_high=high;
    free(y);
    y=NULL;
    y = (double*)malloc(sizeof(double)*(high - low+1) );
    ofstream out(m_str+"_rawdata.txt",std::ios::app);
    out<<"#N\ty\n";
    for(int i=low;i<=high;i++){
        data.Dataset(i,m_n,m_str);
        data.Statistic();
        y[i-low]=data.avestandevia;//The data we need is 'average standard deviation'
        out<<i<<"\t"<<data.avestandevia<<endl;
    }
    out<<"\n\n";
    out.close();
    out.clear();
    m_havedata=1;
}

void smoothing::smooth(int method){
    if(m_high-m_low+1 < 5) cout<<"high-low+1 should larger than 5!\n";
    else{
        if(method==1) method1();
        else if(method==2) method2();
        else cout<<"Wrong choice. This program only have two smoothing methods!\n";
    }

}

void smoothing::method1(){
    int i=0;
    ofstream out(m_str+"_method1.txt",std::ios::app);
    out<<"#N\ty\n";
    // for y[m_low]
    out<<m_low<<"\t"<<0.2*(3*y[0]+2*y[1]+y[2]-y[4])<<endl;
    // for y[m_low+1]
    out<<m_low+1<<"\t"<<0.1*(4*y[0]+3*y[1]+2*y[2]+y[3])<<endl;
    for(i=m_low+2;i<=m_high-2;i++){
        out<<i<<"\t"<<0.2*(y[i-2-m_low]+y[i-1-m_low]+y[i-m_low]+y[i+1-m_low]+y[i+2-m_low])<<endl;
    }
    // for y[m_high-1]
    out<<m_high-1<<"\t"<<0.1*(y[m_high-3-m_low]+2*y[m_high-2-m_low]+3*y[m_high-1-m_low]+4*y[m_high-m_low])<<endl;
    // for y[m_high]
    out<<m_high<<"\t"<<0.2*(-y[m_high-4-m_low]+y[m_high-2-m_low]+2*y[m_high-1-m_low]+3*y[m_high-m_low])<<endl;
    out<<"\n\n";
    out.close();
    out.clear();

}

void smoothing::method2(){
    int i=0;
    ofstream out(m_str+"_method2.txt",std::ios::app);
    out<<"#N\ty\n";
    // for y[m_low]
    out<<m_low<<"\t"<<1.0/70*(69*y[0]+4*y[1]-6*y[2]+4*y[3]-1*y[4])<<endl;
    // for y[m_low+1]
    out<<m_low+1<<"\t"<<1.0/35*(2*y[0]+27*y[1]+12*y[2]-8*y[3]+2*y[4])<<endl;
    for(i=m_low+2;i<=m_high-2;i++){
        out<<i<<"\t"<<1.0/35*(-3*y[i-2-m_low]+12*y[i-1-m_low]+17*y[i-m_low]+12*y[i+1-m_low]-3*y[i+2-m_low])<<endl;
    }
    // for y[m_high-1]
    out<<m_high-1<<"\t"<<1.0/35*(2*y[m_high-4-m_low]-8*y[m_high-3-m_low]+12*y[m_high-2-m_low]+27*y[m_high-1-m_low]+2*y[m_high-m_low])<<endl;
    // for y[m_high]
    out<<m_high<<"\t"<<1.0/70*(-1*y[m_high-4-m_low]+4*y[m_high-3-m_low]-6*y[m_high-2-m_low]+4*y[m_high-1-m_low]+69*y[m_high-m_low])<<endl;
    out<<"\n\n";
    out.close();
    out.clear();

}

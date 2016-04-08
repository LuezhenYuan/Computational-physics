//This program use linear fitting methods to fit no linear data
///////////

//This program contains three files: main.cpp SimpleStatisticsProject.cpp SimpleStatisticsProject.h
//You should compile the first two files together!

//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//!!!!!注意：需要编译器开启支持c++11标准的选项！
//!!!!!Attention: Have your compiler follow the c++11 ISO C++ language standard [-std=c++11]
//!!!!!You can modify your "Global compiler settings": find the "c++11" like term and allow it!
//Compile command: $ g++ -std=c++11 main.cpp SimpleStatisticsProject.cpp -o program
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////

//////////////////////////////////
//Algorithm:
/*
1. Generate standard deviation for average~N
2. Transform the data

ind = 0;
if(y(N) = a e^{bN})
	Y' = lny;N'= N;ind = 1;//lnY = lna + bx
else if(y(N) = a N^b)
	Y' = lny; N' = lnN;ind = 2//lnY = lna + blnN

3. Several average calculation: \bar{x}, \bar{y}, \bar{xy}, \bar{x^2}, n=length(Y');
4. Linear correlation coefficient:

ab=0;a2=0;b2=0;
for i=1:n:
	a = (x_i-\bar{x});
	b = (y_i-\bar{y});
	ab + = a*b;
	a2 += a*a;b2 += b*b;
end for
r = a*b/(a2 * b2)^0.5

5. Linear fitting:

A1 = (\bar{xy} - \bar{x} * \bar{y})/(\bar{x^2} - \bar{x}^2);
A0 = \bar{y} - A1 * \bar{x};

tmp = 0;
for i = 1:n:
	tmp += (yi - A0 - A1 * xi)^2;
sigma = (1/(n-2) * tmp)^0.5;//standard deviation
sigmaA0 = sigma * (\bar{x^2}/(n*\bar{x^2} - \bar{x}^2 ) )^0.5;
sigmaA1 = sigma * (1/(n*\bar{x^2} - \bar{x}^2 ) )^0.5

6. Transform back
a = e^A0;b=A1;

if(ind == 1 or ind == 2)
	y'pred = e(A0 + A1*N');//predicted y
	ypred = e^{y'pred};
	cout<< N<<y<<ypred;
*/
//////////////////////////////////


//Author: Luezhen Yuan
//Last update: 20160320
/////////////////////////////////////////////
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include "SimpleStatisticsProject.h"
using namespace std;

class fitting
{
private:
    SimpleStatisticsProject data;
    string m_str;//file name
    int m_n;//number of interation
    double* y;double* x;
    double* yp;double* xp;
    int m_low,m_high;
    int indaverage;
    int ind;//indicator 1 for y(N) = a e^{bN}, 2 for y(N) = a N^b
    double xbar,ybar,x2bar,xybar;

    void AverageCalculation();//Several average calculation
public:
    fitting():data(),m_str("result"),m_n(1000),y(NULL),x(NULL),yp(NULL),xp(NULL),m_low(1),m_high(1),indaverage(-1),ind(1),xbar(0),ybar(0),x2bar(0),xybar(0){}
    fitting(int N,int n,string str):data(N,n,str,1),m_str(str),m_n(n),y(NULL),x(NULL),yp(NULL),xp(NULL),m_low(1),m_high(1),indaverage(-1),ind(1),xbar(0),ybar(0),x2bar(0),xybar(0){}
    ~fitting();
    void datagenerate(int low=1,int high=50);//Generate standard deviation for average~N
    void Transformdata(int indcator=1);//Transform the data(x->xp;y->yp)
    double LinearCorrCoeff();//Linear correlation coefficient
    void LinearFitting();//Linear fitting, and print the predicted y.
};

int main()
{
    int n=1000,low=1,high=50,ind=1,ex=-1;
    cout<<"Non linear Fitting(Use linear fitting methods)\n";
    string str;//file name
    cout<<"File name:";cin>>str;
    fitting sim(3,n,str);//3 has no use.
    while(1){

        cout<<"n [1000]:";cin>>n;
        cout<<"Low case for N [1]:";cin>>low;
        cout<<"High case for N [50]:";cin>>high;
        if(low>=high) continue;
        cout<<"Fitting model:\n";//Two models
        cout<<"1: y(N) = a e^{bN}\n";
        cout<<"2: y(N) = a N^b\n";
        sim.datagenerate(low,high);
        cout<<"Choose fitting model [1]:";cin>>ind;
        if(ind!=1 &&ind!=2) continue;
        sim.Transformdata(ind);

        sim.LinearCorrCoeff();
        sim.LinearFitting();
        cout<<"Finish fitting!\n\n";
        cout<<"Non linear Fitting(Use linear fitting methods)\n";
        cout<<"1 For continue, -1 for exit:";cin>>ex;
        if(ex!=1) break;
    }


    return 0;
}

fitting::~fitting(){
    free(x);free(y);free(xp);free(yp);//free four arraies
    x=NULL;y=NULL;xp=NULL;yp=NULL;
}

void fitting::datagenerate(int low,int high){
    free(x);free(y);free(xp);free(yp);
    x=NULL;y=NULL;xp=NULL;yp=NULL;
    m_low = low;m_high = high;
    y = (double*)malloc(sizeof(double)*(high - low+1) );
    x = (double*)malloc(sizeof(double)*(high - low+1) );
    yp = (double*)malloc(sizeof(double)*(high - low+1) );
    xp = (double*)malloc(sizeof(double)*(high - low+1) );
    for(int i=low;i<=high;i++){
        data.Dataset(i,m_n,m_str);
        data.Statistic();
        x[i-low] =i;y[i-low]=data.avestandevia;
    }
}

void fitting::Transformdata(int indicator){
    ind = indicator;
    ofstream out(m_str+"_transformeddata.txt",std::ios::app);
    out<<"xp\typ\n";
    if(ind == 1){
        out<<"# y(N) = a e^{bN}\n";
        for(int i=m_low;i<=m_high;i++){
            yp[i-m_low] = log(y[i-m_low]);
            xp[i-m_low] = x[i-m_low];
            out<<xp[i-m_low]<<"\t"<<yp[i-m_low]<<"\n";
        }
    }

    else if(ind == 2){
        out<<"# y(N) = a N^b\n";
        for(int i=m_low;i<=m_high;i++){
            yp[i-m_low] = log(y[i-m_low]);
            xp[i-m_low] = log(x[i-m_low]);
            out<<xp[i-m_low]<<"\t"<<yp[i-m_low]<<"\n";
        }
    }

    indaverage = -1;//Not call AverageCalculation() yet.
    out<<"\n\n";
    out.close();out.clear();
}

void fitting::AverageCalculation(){//Several average calculation
    xbar=0;ybar=0;x2bar=0;xybar=0;
    for(int i=m_low;i<=m_high;i++){
        xbar += xp[i-m_low];
        ybar += yp[i-m_low];
        xybar += xp[i-m_low]*yp[i-m_low];
        x2bar += xp[i-m_low]*xp[i-m_low];
    }
    xbar/=m_high-m_low+1;
    ybar/=m_high-m_low+1;
    xybar/=m_high-m_low+1;
    x2bar/=m_high-m_low+1;
    indaverage = 1;//finish the call of void AverageCalculation();
}

double fitting::LinearCorrCoeff(){//Linear correlation coefficient
    if(indaverage != 1) AverageCalculation();

    double ab=0,a2=0,b2=0;
    double a=0,b=0;
    for(int i=m_low;i<=m_high;i++){
        a=(xp[i-m_low]-xbar);
        b=(yp[i-m_low]-ybar);
        ab += a*b;
        a2 += a*a;b2 += b*b;
    }
    ofstream out(m_str+"_fitting.txt",std::ios::app);
    double result=ab/sqrt(a2 * b2);
    out<<"Linear correlation coefficient:"<<result<<endl;
    cout<<"Linear correlation coefficient:"<<result<<endl;
    out.close();out.clear();
    return result;
}

void fitting::LinearFitting(){//Linear fitting
    if(indaverage != 1) AverageCalculation();
    double A1 = (xybar-xbar*ybar)/(x2bar-xbar*xbar);
    double A0 = ybar-A1*xbar;

    double tmp=0;
    for(int i=m_low;i<=m_high;i++){
        tmp+=(yp[i-m_low] - A0-A1*xp[i-m_low])*(yp[i-m_low] - A0-A1*xp[i-m_low]);
    }
    int n = m_high-m_low+1;
    double sigma = sqrt(1.0/(n-2) * tmp);//standard deviation
    double sigmaA0 = sigma * sqrt(x2bar/(n*x2bar - xbar*xbar ) );
    double sigmaA1 = sigma * sqrt(1/(n*x2bar - xbar*xbar ) );
    ofstream out(m_str+"_fitting.txt",std::ios::app);
    out<<"Standard deviation of fitting:"<<sigma<<endl;
    out<<"A0:"<<A0<<"\t"<<"Standard deviation of A0:"<<sigmaA0<<endl;
    out<<"A1:"<<A1<<"\t"<<"Standard deviation of A1:"<<sigmaA1<<endl;

    //Transform back
    double a = exp(A0);double b=A1;
    if(ind==1){
    out<<"Final model:y(N) = "<<a<<"e^"<<b<<"N\n";
    cout<<"Final model:y(N) = "<<a<<"e^"<<b<<"N\n";
    }
    else if(ind == 2){
    out<<"Final model:y(N) = "<<a<<"N^"<<b<<"\n";
    cout<<"Final model:y(N) = "<<a<<"N^"<<b<<"\n";
    }
    double yppred=0,ypred=0;

    out<<"x\ty\tpredicted y\n";
    if(ind==1 || ind==2){
        for(int i=m_low;i<=m_high;i++){
            yppred=A0+A1*xp[i-m_low];
            ypred = exp(yppred);
            out<<x[i-m_low]<<"\t"<<y[i-m_low]<<"\t"<<ypred<<"\n";
        }
    }
    out<<"\n\n";
    out.close();out.clear();
}

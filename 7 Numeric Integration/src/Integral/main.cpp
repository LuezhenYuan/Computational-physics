//This program implement 'Adaptive Simpson' method(变步长辛卜生法) and 'Trapezoidal' method(梯形法) to calculate integration numerically.
//In the macro, f(x) is defined as a density function of Gauss Distribution. the mean is 50, the standard error is 15.
//The default parameters 'low=0,up=100', which means the function 'AdaptiveSimpson' integrate f(x) from 0 to 100.

//Constains on parameters:
//'epsilon' couldn't be lower than 10 decimal place(小数点后10位).
///////////////

//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//Compile command: $ g++ main.cpp -o a.out
//To run the program, just $ ./a.out
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////


//Author: Luezhen Yuan
//Last update: 20160402
/////////////////////////////////////////////

#include <iostream>
#include <cstdio>
#define f(x) 1.0/(15*sqrt(2*pi))*exp(-0.5*(( (x+(low+up)/2) -50)/15)*(( (x+(low+up)/2) -50)/15) )
#include <cmath>
using namespace std;

double pi=acos(-1);
double AdaptiveSimpson(const double low,const double up,const double epsilon);
double trapezoidal(const double low,const double up,const double epsilon);
int main()
{

    double epsilon=0.001;
    int ex=-1;
    cout << "Numeric Integration" << endl;
    while(1){
    cout<<"epsilon [0.001]:";cin>>epsilon;//precision. epsilon couldn't be lower than 10 decimal place(小数点后10位).
    cout<<"Simpson rule:\n";
    printf("Result: %.10f\n",AdaptiveSimpson(0,100,epsilon) );//integrate f(x) from 0 to 100.
    cout<<"Trapezoidal rule:\n";
    printf("Result: %.10f\n",trapezoidal(0,100,epsilon) );//integrate f(x) from 0 to 100.

    cout<<"Exit -1. Continue 1 [-1]:";cin>>ex;
    if(ex==-1) break;
    }

    return 0;
}

double AdaptiveSimpson(const double low,const double up,const double epsilon=0.001){
    const double A=(up-low)/2;
    double H=4*A;double RC=0;double RP=f(-A)+f(A);
    int i=0;
    double err=epsilon+1;
    double tmp=0;
    double S=f(A)*2*A;//prevent 'tmp' and 'S' happened to be extremely similar at the first iteration.

    while(err>epsilon){
        H=H/2;
        RP=RP+2*RC;
        RC=0;
        for(int k=1;k<=exp2(i);k++)
            RC+=f(-A-H/2+k*H);
        tmp=H/6*(RP+4*RC);
        err=abs(S-tmp);
        S=tmp;
        i++;
    }
    cout<<"Converge at "<<i<<"th iteration.\n";
    return S;
}

double trapezoidal(const double low,const double up,const double epsilon=0.001){
    int j=0;
    const double A=(up-low)/2;
    double h=A*2;
    double T=h/2*(f(-A)+f(A));//T stores the integration result.
    double s=0;
    double tmp=0;
    double err=epsilon+1;
    while(err>epsilon){
        j++;
        h/=2;
        s=0;
        for(int k=1;k<=exp2(j-1);k++) s+=f(-A+h*(2*k-1));
        tmp=T/2+s*h;
        err=abs(T-tmp);
        T=tmp;
    }
    cout<<"Converge at "<<j<<"th iteration.\n";
    return T;
}

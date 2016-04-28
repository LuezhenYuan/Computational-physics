//This program use numeric method to solve PDEs in the content of Thermal Conduction
//\frac{\partial u}{\partial t}
//= \lambda (\frac{\partial^2 u}{\partial x^2}
//  +\frac{\partial^2 u}{\partial y^2}+\frac{\partial^2 u}{\partial z^2})

////
//Restriction on parameters:
//alpha<0.5, where alpha=tau*lambda/h^2.
//  tau is the length of one time step, h is the length of one special step.
//  lambda=K/(c*rho) >0
////

////
//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//Compile command: $ g++ -std=c++11 main.cpp -o program.out
//To run the program, just $ ./a.out
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////

////
//Author: Luezhen Yuan
//Last update: 20160410
/////////////////////////////////////////////
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;
void Thermal_Conduction(string file_name);
int main()
{
    cout << "Thermal Conduction:\n--- A partial differential equation." << endl;
    Thermal_Conduction("result");
    return 0;
}
void Thermal_Conduction(string file_name){
    ofstream out(file_name+".txt",ios::app);
    //parameters of Thermal conduction
    double alpha=1.0/6;
    double lambda=1;
    double h=0.1;//length of special step
    double T=0.06;//t_max
    double tau;
    tau=alpha*h*h/lambda;
    int M=T/tau;
    int N=1.0/h;

    int k;//index of mesh of time
    double * u;//temprature
    int i;//index of mesh of space
    u=(double*)malloc(sizeof(double)*(N+1));

    double* u_tmp;
    u_tmp=(double*)malloc(sizeof(double)*(N+1));

    out<<"#i\tk\tu\n";
    for(i=0;i<=N;i++){
        u[i]=4*i*h*(1-i*h);//!!!!Initial condition
        out<<i<<"\t"<<0<<"\t"<<u[i]<<endl;
    }
    u_tmp[0]=0;u_tmp[N]=0;//!!!!Boundary condition


    for(k=1;k<=M;k++){
        for(i=1;i<N;i++){
            u_tmp[i]=alpha*u[i+1]+alpha*u[i-1]+(1-2*alpha)*u[i];
        }
        for(i=0;i<=N;i++){
            u[i]=u_tmp[i];
            out<<i<<"\t"<<k<<"\t"<<u[i]<<endl;
        }
    }
    out.close();out.clear();
}


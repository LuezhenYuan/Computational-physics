//This program use Runge Kutta method to solve ODEs of the form
// dx
// -- = f(x,t)
// dt
//
//with
//x(t_0)=x_0
////
//  The function 'void Runge_Kutta()' is implemented in a very general form.
// It means that if you have another ODEs system, you can write your own f1, f2,
// ..., and provide initial value of the dependent variables. You don't need
// to change anything in the function 'void Runge_Kutta()', no matter what the number
// of the dependent variables(and corresponding derivatives) is!

////
//This program's default f1, f2 is from the content of
//RLC circuit:
//f1(Q,T,t)=I,f2(Q,I,t)=1/L(Va-Q/C-IR)
//I0=0,Q0=0
//lambda=R/2*sqrt(C/L). lambda<1, lambda=1, and lambda>1 will affect the behaviour of the system.

////
//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//Compile command: $ g++ -std=c++11 main.cpp -o program.out
//To run the program, just $ ./a.out
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////

////
//Author: Luezhen Yuan
//Last update: 20160409
/////////////////////////////////////////////

//A thinking procedure -- from a specific RCL circuit system to a generalized ODEs system
/*
Generalization procedure:

1. Normal derivatives
double f1(double t, double x1,double x2){//
    return x2;
}

double f2(double t, double x1,double x2){//
    return 1/L*(Va-x1/C-x2*R);
}

2. Use array to store dependent variables
double f1(double t, double* x){//
    return x[2];
}
double f2(double t, double* x){//
    return 1/L(Va-x[1]/C-x[2]*R);
}

3. Common form of these two derivatives -- using function pointer
double (*pf)(double t,double* x);//(*pf)(t,x)

4. Array of function pointers
double (*pf[])(double t,double* x);//(*pf[1])(t,x)

5. Use two array as parameters in the function 'void Runge_Kutta()'
void Runge_Kutta(double (*pf[])(double t,double* x),double* xn,int N_dependent_variable,double t_high,int N_t_steps,string file_name);//length pf==length x
*/
#include <iostream>
#include <cstdlib>//malloc and free
#include <iostream>//std::cout, std::endl;
#include <fstream>//std::ofstream
#include <string>//std::string
using namespace std;

// A generalized form for solving a ODEs system
void Runge_Kutta(double (*pf[])(double t,double* x),double* xn,int N_dependent_variable,double t_high,int N_t_steps,string file_name);//length pf==length x

//The system of ordianry differencial equations
double f1(double t, double* x){//
    return x[1];
}
double f2(double t, double* x){//
    return 1.0/4*(5-x[0]/1-x[1]*8);
}

int main()
{
    cout << "Runge Kutta method.\n" << endl;
    double (*pf[])(double t,double* x)={f1,f2};//array of function pointers, which point to f1() and f2()
    double*x;
    x=(double*)malloc(sizeof(double)*2);
    x[1]=0,x[2]=0;//Initial state
    Runge_Kutta(pf,x,2,50,5000,"result.txt");//Run the Runge_Kutta solver
    return 0;
}

void Runge_Kutta(double (*pf[])(double t,double* x),double* xn,int N_dependent_variable,double t_high,int N_t_steps,string file_name){//t from zero to t_high
    double* k1;k1=(double*)malloc(sizeof(double)*N_dependent_variable);
    double* k2;k2=(double*)malloc(sizeof(double)*N_dependent_variable);
    double* k3;k3=(double*)malloc(sizeof(double)*N_dependent_variable);
    double* k4;k4=(double*)malloc(sizeof(double)*N_dependent_variable);
    int i,j;
    double tn,t_step;
    t_step=t_high/N_t_steps;

    double* x_tmp;
    x_tmp=(double*)malloc(sizeof(double)*N_dependent_variable);

    ofstream out;
    out.open(file_name,ios_base::app);
    out<<"#t";//print the first line in the output file
    for(i=0;i<N_dependent_variable;i++){
        out<<"\t"<<"x"<<i;
    }
    out<<endl;

    out<<0;//This is the initial state
    for(i=0;i<N_dependent_variable;i++){
        out<<"\t"<<xn[i];
    }
    out<<endl;

    tn=0;
    for(j=0;j<N_t_steps;j++){
        //k1
        for(i=0;i<N_dependent_variable;i++){
            k1[i]=(*pf[i])(tn,xn);
        }
        //k2
        for(i=0;i<N_dependent_variable;i++){
            x_tmp[i]=xn[i]+t_step/2*k1[i];
        }
        for(i=0;i<N_dependent_variable;i++){
            k2[i]=(*pf[i])(tn+t_step/2,x_tmp);
        }
        //k3
        for(i=0;i<N_dependent_variable;i++){
            x_tmp[i]=xn[i]+t_step/2*k2[i];
        }
        for(i=0;i<N_dependent_variable;i++){
            k3[i]=(*pf[i])(tn+t_step/2,x_tmp);
        }
        //k4
        for(i=0;i<N_dependent_variable;i++){
            x_tmp[i]=xn[i]+t_step*k3[i];
        }
        for(i=0;i<N_dependent_variable;i++){
            k4[i]=(*pf[i])(tn+t_step,x_tmp);
        }
        //update xn
        for(i=0;i<N_dependent_variable;i++){
            xn[i]=xn[i]+1.0/6*(k1[i]+2*k2[i]+2*k3[i]+k4[i])*t_step;
        }
        tn+=t_step;
        out<<tn;
        for(i=0;i<N_dependent_variable;i++){
            out<<"\t"<<xn[i];
        }
        out<<endl;
    }
    out<<"\n\n";
    out.close();out.clear();
    free(k1);free(k2);free(k3);free(k4);
    return;
}

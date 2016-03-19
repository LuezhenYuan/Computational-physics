//This program implement Lagrange interpolating
//The target function is "1/sqrt(2*pi)/15*exp(-0.5*((x-50)/15)*((x-50)/15))", which is probability density of normal distribution
/////////////////
//Constrain for parameter:
//x0,xn: no constrain
//n: no constrain. But n<10 is better to see the ability of interpolating
//e.g.: x0=5,xn=95,n=6,file name = "result"
/////////////////
//Algorithm
//
//Input: x0 xn n
//Output: matrix of x,predicted value y,the real value yreal
//
//calculate xi,yi,and store in the vector x, and y
//for xt=x0:0.01:xn
//	result=0;
//	for j=0:n
//		Aj=1;
//		for i=0:n
//			if i!=j
//				Aj*=(xt-x[i])/(x[j]-x[i])
//		result+=Aj*y[j]
//	print xt,result,yreal
//End
////////////////

//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////

//Author: Luezhen Yuan
//Last update: 20160312
/////////////////////////////////////////////



#include <iostream>//std::cout,std::cin
#include <cstdlib>//malloc()
#include <cmath>//acos()
#include <fstream>//ofstream
#include <string>//std::string
using namespace std;
void interpolating(double x0,double xn,int n,string str);

int main()
{
    double x0=0,xn=0;//data range
    int n=0,i=1;
    string str;//file name
    cout << "Interpolating using Lagrange polynomial" << endl;
    while(1){
    if(i!=1) break;
    cout << "x0:";cin>>x0;
    cout << "xn:";cin>>xn;
    cout << "n:";cin>>n;
    cout<<"Output file name:";cin>>str;
    interpolating(x0,xn,n,str);//run the function
    cout <<"Interpolating Done!\n----------------\n";
    cout<<"\n0-Exit, 1-Continue:";cin>>i;
    }
    return 0;
}

void interpolating(double x0,double xn,int n,const string str){
    double* x;double* y;
    x = (double*)malloc(sizeof(double)*(n+1));
    y = (double*)malloc(sizeof(double)*(n+1));
    ofstream out;
    out.open(str.c_str(),ios_base::app);//open the file
    double pi=acos(-1);//pi is used in the target function "1/sqrt(2*pi)/15*exp(-0.5*((x-50)/15)*((x-50)/15))"

    //calculate xi,yi,and store in the vector x, and y
    out<<"#sample data\nx\ty\n";//generate n+1 sample points
    for(int i=0;i<n+1;i++){
    x[i]=x0+i*(xn-x0)/n;
    y[i]=1/sqrt(2*pi)/15*exp(-0.5*((x[i]-50)/15)*((x[i]-50)/15));
        out<<x[i]<<"\t"<<y[i]<<endl;
    }
    out<<"\n\n";
    int j=0,i=0;
    double result=0;
    double Aj=1;

    out<<"#interpolating points and real one\nx\ty\tyreal\n";
    //calculate many points for drawing
    double interval = (xn-x0)/100;
    double xt=0;
    for(xt=x0;xt<=xn;xt+=interval){
        result=0;
        for(j=0;j<n+1;j++){
            Aj=1;
            for(i=0;i<n+1;i++)
                if(i!=j) Aj*=(xt-x[i])/(x[j]-x[i]);

            result+=Aj*y[j];
        }
        out<<xt<<"\t"<<result<<"\t"<<1/sqrt(2*pi)/15*exp(-0.5*((xt-50)/15)*((xt-50)/15))<<endl;
    }
    if(xt>xn) out<<xn<<"\t"<<y[n]<<"\t"<<y[n]<<endl;
    out<<"\n\n";
    out.close();out.clear();
    free(x);free(y);

}

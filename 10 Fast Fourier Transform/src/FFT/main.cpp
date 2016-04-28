//This program implement the fast fourier transform
//double* periodic_sampling(); is used to generate data points from the function x(t)
//void FFT(double* const data); is used to perform a fast fourier transform on the data.

//To change the function used for generating data, you should shrink the cycle to 2*pi
//
//To call the 'FFT()' for your own data, the number of data points should be N=2^r.

/////
//Restriction on the parameters:
//N=2^r
//the cycle should be 2*pi
/////

////
//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//Compile command: $ g++ main.cpp -o FFT.out
//To run the program, just $ ./FFT.out
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////

////
//Author: Luezhen Yuan
//Last update: 20160417
/////////////////////////////////////////////



#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#define pi 3.1415926
#define x(t) cos(t)+0.5*cos(2*(t))+0.8*cos(5*(t))
#define r 6
#define N 64
#define w_real(n) cos(-2*(n)*pi/N)
#define w_imag(n) sin(-2*(n)*pi/N)
#define file "result.txt"
// The cycle is 2*pi
using namespace std;
double* periodic_sampling();
void FFT(double* const data);
int main()
{
    cout << "Fast Fourier Transform." << endl;
    double* data;
    data=periodic_sampling();//get 64 data points.
    FFT(data);//call the fast fourier transform funciton, and print the output to 'result.txt'
    free(data);
    return 0;
}

double* periodic_sampling(){
    int i;
    double* data;
    data=(double*)malloc(sizeof(double)*N);
    for(i=0;i<N;i++){
        data[i]=x(1.0*i/N *2*pi);//periodic sampling
        //cout<<i<<"\t"<<data[i]<<"\n";
    }
    return data;
}

void FFT(double* const data){
    int l;//The l level in the FFT flow chart(calculate from 1)
    int jump;
    int n;//The nth node in the FFT flow chart, in other word, the nth row(calculate from 1)
    int p;
    int j;
    int tmp1,tmp2;
    int step;
    double FFTdata_real[N];
    double FFTdata_imag[N];

    double FFTresult_real[N];
    double FFTresult_imag[N];

    double w_value_real,w_value_imag;
    double tmp3_real,tmp3_imag;
    for(n=0;n<N;n++){
        FFTdata_real[n]=data[n];
        FFTdata_imag[n]=0;
    }
    for(l=1;l<=r;l++){
        jump=0;
        step=exp2(r-l);
        for(n=jump;n<jump+step;n++){
            tmp1=n>>(r-l);
            tmp2=0;
            for(j=1;j<=l;j++){
                tmp2=tmp1%2+tmp2*2;
                tmp1>>=1;
            }
            tmp2*=step;
            p=tmp2;
            //cout<<"p: "<<p<<"\n";
            w_value_real=w_real(p);
            w_value_imag=w_imag(p);
            tmp3_real=w_value_real*FFTdata_real[n+step]-w_value_imag*FFTdata_imag[n+step];
            tmp3_imag=w_value_imag*FFTdata_real[n+step]+w_value_real*FFTdata_imag[n+step];
            FFTdata_real[n]+=tmp3_real;
            FFTdata_imag[n]+=tmp3_imag;
            FFTdata_real[n+step]=FFTdata_real[n]-2*tmp3_real;
            FFTdata_imag[n+step]=FFTdata_imag[n]-2*tmp3_imag;
            if(n+1==jump+step){
                jump+=2*step;
                n=jump-1;
                if(n>=N-1) break;
            }
        }
        //cout<<"l: "<<l<<endl;
    }

    int index;
    for(n=0;n<N;n++){
        index=0;
        tmp1=n;
        for(j=1;j<=r;j++){
            index=tmp1%2+index*2;
            tmp1>>=1;
        }
        //cout<<index<<endl;
        FFTresult_real[index]=FFTdata_real[n];
        FFTresult_imag[index]=FFTdata_imag[n];
    }
    ofstream out(file);
    out<<"#t\tRaw_data\tf_k\tFFT_real\tFFT_imag\tFFT_modulus\n";//f_t is the frequence
    for(n=0;n<N;n++){
        out<<1.0*n/N *2*pi<<"\t"<<data[n]<<"\t"<< 1.0*n/2/pi<<"\t"<<FFTresult_real[n]<<"\t"<<FFTresult_imag[n]<<"\t"<<sqrt(FFTresult_real[n]*FFTresult_real[n]+FFTresult_imag[n]*FFTresult_imag[n])<<"\n";
    }
    out<<"\n\n";
    out.close();out.clear();
}

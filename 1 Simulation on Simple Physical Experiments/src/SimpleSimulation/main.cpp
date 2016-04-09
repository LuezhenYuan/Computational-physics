//This program can simulate three simple physical experiments: 1)Simple Harmonic Vibration, 2)Multiple Slit Diffraction, and 3) alpha particle scattering.
//1)'Simple Harmonic Vibration' simulation
//void SimpleHarmonicVibration(); is used to simulate 'Simple Harmonic Vibration'.
//Constrain: w1,w2 <= 0.3 is good for draw figure smoothly
//e.g.: A1=1,A2=1,w1=0.1,w2=0.1,phi1=0,phi2=1
//////
//2)'Multiple Slit Diffraction' simulation
//void MultipleSlitDiffraction(); is used to simulate 'Multiple Slit Diffraction'
//Constrain: 0<lamb<a<d && a d in the same magnitude && a/lamb is around 100
//e.g. a=0.05(mm), d=0.1(mm), lamb=590(nm), I0=1, N=1
//////
//3)'alpha particle scattering' simulation
//void AlphaParticleScattering(); is used to simulate 'alpha particle scattering'
//Constrain: Not clear
//e.g.: k=0.75,x0=0,y0=0,x=-4,y=0,vx=1,vy=0.5
/////////////////////////////////////////////

//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////

//Author: Luezhen Yuan
//Last update: 20160307
/////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>//std::numetic_limits::infinity()
using namespace std;
void SimpleHarmonicVibration();
void MultipleSlitDiffraction();
void AlphaParticleScattering();
int main()
{
    int i=0;
    while(1){
        cout<<"Simple Simulation in Physics"<<endl;
        cout<<"0--Exit\n";
        cout<<"1--Simple Harmonic Vibration\n";
        cout<<"2--Multiple Slit Diffraction\n";
        cout<<"3--Alpha Particle Scattering\n";
        cout<<"Which simulation do you want to run?"<<endl;cin>>i;

        switch(i){
        case 0:return 0;break;
        case 1:SimpleHarmonicVibration();break;
        case 2:MultipleSlitDiffraction();break;
        case 3:AlphaParticleScattering();break;
        default:cout<<"Wrong number\n";
        }
    }


    return 0;
}

void SimpleHarmonicVibration(){
    cout<<"Simulation for the experiments of simple harmonic vibration\n";
    cout<<"Please type in the several parameters\n";
    int N=0;
    double x1=0,x2=0,x=0;
    double A1=0,A2=0,w1=0,w2=0,phi1=0,phi2=0;//parameters
    ofstream out;//file handler
    string str;//used to store file name

    int t=0;
    int i=0;
    const double pi = acos(-1);//a good way to get the value of pi
    while(1){
        cout<<"\nType 1 to continue a simulation,0 to exit:";cin>>i;
        if(i==0) return;//Stop iteration

        //Put in parameters
        cout<<"A1 A2:";cin>>A1>>A2;
        cout<<"w1 w2:";cin>>w1>>w2;
        cout<<"phi1(pi) phi2(pi):";cin>>phi1>>phi2;
        cout<<"N:";cin>>N;

        cout<<"output file name:";
        cin>>str;

        //check whether the parameter set is right
        cout<<"\nPlease check your parameters:\n";
        cout<<"A1: "<<A1<<"\tA2: "<<A2<<"\nw1: "<<w1<<"\tw2: "<<w2<<"\nphi1: "<<phi1<<"pi\tphi2: "<<phi2<<"pi"<<endl;
        cout<<"If something wrong, please type 0. If continue, type 1:";cin>>i;
        if(!i){continue;}

        try{
            out.open(str,ios::app);//open the file
        }
        catch(...){
            cout<<"Couldn't open the file\n";
            continue;
        }

        //output to file
        out<<"#A1: "<<A1<<"\tA2: "<<A2<<"\n#w1: "<<w1<<"\tw2: "<<w2<<"\n#phi1: "<<phi1<<"pi\tphi2: "<<phi2<<"pi"<<endl;

        phi1*=pi;phi2*=pi;
        out<<"x1,x2,x,t\n";
        try{
            for(t=0;t<N;t++){
                x1 = A1*cos(w1*t+phi1);
                x2 = A2*cos(w2*t+phi2);
                x = x1+x2;
                if(abs(x)<0.000001) x=0;
                out<<x1<<','<<x2<<','<<x<<','<<t<<endl;
            }
            out<<"\n\n";
        }
        catch(...){
            cout<<"Something wrong when printing to the file!"<<endl;
            continue;
        }
        cout<<"Simulation Done!\n";
        out.clear();out.close();
    }

    return;
}

//Simulation for MultipleSlitDiffraction
//Constraint: 0<lamb<a<d && a d in the same magnitude && a/lamb is around 100 && N>0 && I0>0
//e.g. a=0.05(mm), d=0.1(mm), lamb=590(nm), I0=1, N=1
void MultipleSlitDiffraction(){
    cout<<"Simulation for the experiments of Multiple Slit Diffraction\n";
    cout<<"Please type in the several parameters\n";
    double a=0,d=0,lamb=0,I0=1,I=0;//parameters
    double theta=0;
    double u=0,v=0;

    int N=1;
    string str;
    ofstream out;
    int i=1;
    const double pi = acos(-1);
    double tmp1=0,tmp2=0;//store temperory value
    while(1){
        cout<<"\nType 1 to continue a simulation,0 to exit:";cin>>i;
        if(i==0) return;

        cout<<"a(mm) d(mm):";cin>>a>>d;
        cout<<"lambda(nm):";cin>>lamb;
        cout<<"I0:";cin>>I0;
        cout<<"N:";cin>>N;
        cout<<"file:";cin>>str;

        //check
        cout<<"\nPlease check your parameters:\n";
        cout<<"a(mm): "<<a<<"\td(mm): "<<d<<"\nlambda(nm): "<<lamb<<"\nI0: "<<I0<<"\nN: "<<N<<endl;
        cout<<"If something wrong, please type 0. If continue, type 1:";cin>>i;
        if(!i){continue;}

        try{
            out.open(str,ios::app);//open the file
        }
        catch(...){
            cout<<"Couldn't open the file\n";
            continue;
        }



        out<<"#a(mm): "<<a<<"\td(mm): "<<d<<"\n#lambda(nm): "<<lamb<<"\n#I0: "<<I0<<"\n#N: "<<N<<endl;
        a/=1000;d/=1000;lamb/=1000000000;//change to meter
        out<<"theta,I\n";
        try{
            for(theta=0;theta<0.1;theta+=0.0001){
                u = pi/lamb*a*sin(theta);
                v = pi/lamb*d*sin(theta);

                tmp1=sin(u)/u;
                if(tmp1!=tmp1) tmp1=1;//When tmp1==nan(Not A Number, it happens when the denominator is 0.0),tmp1!=tmp1 is true!
                if(tmp1== numeric_limits<double>::infinity()) break;//Check whecher the value is infinity. However, I think this condition will not occur at any time

                tmp2=sin(N*v)/sin(v);
                if(tmp2!=tmp2) tmp2=N;
                if(tmp2== numeric_limits<double>::infinity()) break;

                I = I0*pow(tmp1,2)*pow(tmp2,2);
                //if(I<0.001) I=0;
                out<<theta<<','<<I<<"\n";
                out<<-theta<<','<<I<<"\n";
            }
            out<<"\n\n";
        }
        catch(...){
            cout<<"Something wrong when printing to the file!"<<endl;
            continue;
        }
        cout<<"Simulation Done!\n";
        out.clear();out.close();

    }
}

//Simulation for Alpha Particle Scattering
//Constraint: (x,y) != (x0,y0)
//e.g.
void AlphaParticleScattering(){
    cout<<"Simulation for the experiments of Alpha Particle Scattering\n";
    cout<<"Please type in the several parameters\n";
    double k=0,x0=0,y0=0,x,y,vx,vy,ax,ay;
    string str;
    ofstream out;
    double t=0,R3=0;
    int i=0;
    while(1){
        cout<<"\nType 1 to continue a simulation,0 to exit:";cin>>i;
        if(i==0) return;

        cout<<"k:";cin>>k;
        cout<<"x0 y0:";cin>>x0>>y0;
        cout<<"x y:";cin>>x>>y;
        cout<<"vx vy:";cin>>vx>>vy;
        cout<<"file:";cin>>str;

         //check
        cout<<"\nPlease check your parameters:\n";
        cout<<"k: "<<k<<"\nx0: "<<x0<<"\ty0: "<<y0<<"\nx: "<<x<<"\ty: "<<y<<"\nvx:"<<vx<<"\tvy:"<<vy<<endl;
        cout<<"If something wrong, please type 0. If continue, type 1:";cin>>i;
        if(!i){continue;}

        //open the file, waiting for the output
        try{
            out.open(str,ios::app);//open the file
        }
        catch(...){
            cout<<"Couldn't open the file\n";
            continue;
        }

        out<<"#k: "<<k<<"\n#x0: "<<x0<<"\ty0: "<<y0<<"\n#x: "<<x<<"\ty: "<<y<<"\n#vx"<<vx<<"\tvy"<<vy<<endl;
        out<<"x,y\n";
        try{
            for(t=0;t<5;t+=0.05){//dt=0.05
                R3 = pow(pow(x-x0,2)+pow(y-y0,2),3/2);
                ax = k*(x-x0)/R3;
                if(ax== numeric_limits<double>::infinity()) throw 1;//Check whecher the value is infinity.
                ay = k*(y-y0)/R3;
                if(ax== numeric_limits<double>::infinity()) throw 1;//Check whecher the value is infinity.
                vx += 0.05*ax;//dt=0.05
                vy += 0.05*ay;
                x+=0.05*vx;y+=0.05*vy;
                out<<x<<','<<y<<endl;
            }
            out<<"\n\n";
        }
        catch(int){
            cout<<"Stop! An infinity value occur!\n";
            continue;
        }
        catch(...){
            cout<<"Something wrong when printing to the file!"<<endl;
            continue;
        }
        cout<<"Simulation Done!\n";
        out.clear();out.close();
    }
}

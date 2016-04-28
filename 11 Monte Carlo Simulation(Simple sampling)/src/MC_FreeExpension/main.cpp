//This program use the Monte Carlo Method to simulate two process: 1) Free expansion. 2) Network growth
//The first simualtion is fast, the second will take a while.

//It's not good to put them together...

////
//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//Compile command: $ g++ -std=c++11 main.cpp -o MonteCarlo.out
//To run the program, just $ ./MonteCarlo.out
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////

////
//Author: Luezhen Yuan
//Last update: 20160417
/////////////////////////////////////////////
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#define generators(i) generator_##i
using namespace std;
//Free expansion
void free_expension(int N,int n,int m,string file);

//Network growth
typedef struct node node;
struct node{
    int degree;
    node* next;
};
struct Network{
    node* dummy_head;
    int Num;//number of nodes
};
void Random_Network_Growth(int initial_number_of_nodes,int growth_steps,int fixed_new_link_with_new_node,string file);
void add_node(int degree,Network& net);
node* run_to(int index,const Network& net);
void degree_list(const Network& net,string file);
int* unique_random_int(int n,Network net,int initial_number_of_nodes,int fixed_new_link_with_new_node,int new_seed=0);

int main()
{
    int ind;
    int m;
    cout<<"Monte Carlo Simulation.\n";
    cout<<"1 for Free Expansion; 2 for Random network growth. [1]:";
    cin>>ind;
    if(ind==1){
        int N,n;
        cout << "Monte Carlo Simulation on the Free Expansion" << endl;
        cout<<"Number of molecules [10000]:";cin>>N;
        cout<<N<<"\nNumber of configuration [1000]:";cin>>m;
        cout<<m<<"\nNumber of time steps for each configuration [>"<<N<<"]:";cin>>n;
        cout<<n<<endl;
        free_expension(N,n,m,"result");
    }
    else if(ind==2){
        cout<<"Number of configuration [10]:";cin>>m;
        int i;
        int initial_number_of_nodes,growth_steps,fixed_new_link_with_new_node;
        cout<<"initial_number_of_nodes [4]:";cin>>initial_number_of_nodes;
        cout<<"growth_steps [10000]:";cin>>growth_steps;
        cout<<"fixed_new_link_with_new_node:";cin>>fixed_new_link_with_new_node;
        for(i=0;i<m;i++){
            Random_Network_Growth(initial_number_of_nodes,growth_steps,fixed_new_link_with_new_node,"result_Random_Network_"+to_string(i)+".txt");
        }

    }


    return 0;
}

//    ------------------      ------------------
//    |  . . . |        |     |   .     .    .  |
//    |  . A . |    B   | --> |      .     .    |
//    |  . . . |        |     |    .      .     |
//    ------------------      ------------------
void free_expension(int N,int n,int m,string file){//m configuration, each runing n time steps. The number of molecules is N.
    int i,j,k;
    char* state_of_molecules;
    int* number_of_mole_in_right;
    int current_number_of_mole_in_right;

    std::random_device rd;
    minstd_rand0 generator_0;
    minstd_rand generator_1;
    mt19937 generator_2;
    std::mt19937_64 generator_3;
    ranlux24_base generator_4;
    ranlux48_base generator_5;
    ranlux24 generator_6;
    ranlux48 generator_7;
    knuth_b generator_8;
    default_random_engine generator(rd());//used to choose the abolve 0~8 generators.
    std::uniform_real_distribution<double> dr(0,1);
    state_of_molecules=(char*)malloc(sizeof(char)*N);
    number_of_mole_in_right=(int*)malloc(sizeof(int)*n);
    ofstream out;
    int p;//which generator is used.
    for(j=0;j<n;j++)
        number_of_mole_in_right[j]=0;

    for(i=0;i<m;i++){
        p=int(dr(generator)*9);

        out.open(file+"_configuration_"+to_string(i)+".txt");
        out<<"Runs: "<<i<<endl;
        out<<"generator used: "<<p<<endl;

        switch(p){//Choose one generator. I couldn;t use generators(p).seed(rd()), because the compiler will view this as generator_p.
        case 0:generators(0).seed(rd());break;
        case 1:generators(1).seed(rd());break;
        case 2:generators(2).seed(rd());break;
        case 3:generators(3).seed(rd());break;
        case 4:generators(4).seed(rd());break;
        case 5:generators(5).seed(rd());break;
        case 6:generators(6).seed(rd());break;
        case 7:generators(7).seed(rd());break;
        case 8:generators(8).seed(rd());break;
        }
        //generators(p).seed(rd());//reset the seed, new configuration
        for(j=0;j<N;j++)
            state_of_molecules[j]=1;//1 indicate left, -1 indicate right

        current_number_of_mole_in_right=0;
        out<<current_number_of_mole_in_right<<endl;
        for(j=1;j<n;j++){//number_of_mole_in_right[0] is always 0
            switch(p){
            case 0:k=int(dr(generators(0))*N);break;
            case 1:k=int(dr(generators(1))*N);break;
            case 2:k=int(dr(generators(2))*N);break;
            case 3:k=int(dr(generators(3))*N);break;
            case 4:k=int(dr(generators(4))*N);break;
            case 5:k=int(dr(generators(5))*N);break;
            case 6:k=int(dr(generators(6))*N);break;
            case 7:k=int(dr(generators(7))*N);break;
            case 8:k=int(dr(generators(8))*N);break;
            }
            //k=int(dr(generators(p))*N);
            state_of_molecules[k]*=-1;
            current_number_of_mole_in_right-=state_of_molecules[k];
            number_of_mole_in_right[j]+=current_number_of_mole_in_right;
            out<<current_number_of_mole_in_right<<endl;
        }
        out<<"\n\n";out.close();out.clear();
    }
    out.open(file+"_average_configuration.txt");
    out<<"Average_configuration\n\n";
    for(j=0;j<n;j++){
        number_of_mole_in_right[j]/=1.0*m;
        out<<number_of_mole_in_right[j]<<endl;
    }
    out<<"\n\n";out.close();out.clear();

}


//fixed_new_link_with_new_node should larger than initial_number_of_nodes
void Random_Network_Growth(int initial_number_of_nodes,int growth_steps,int fixed_new_link_with_new_node,string file){
    Network net;
    net.dummy_head=(node*)malloc(sizeof(node));//The degree list is indexed from 1. 0 for dummy head.
    net.Num=0;
    int i,j;
    for(i=1;i<=initial_number_of_nodes;i++){
        add_node(initial_number_of_nodes-1,net);
    }

    //check:
    //degree_list(net);
    int* neighbour;
    int k;
    node* pr;
    unique_random_int(1,net,initial_number_of_nodes,fixed_new_link_with_new_node,1);//just make the function use new seed.
    for(j=1;j<=growth_steps;j++){
    //cout<<j<<",";

        //cout<<net.Num<<endl;
        neighbour=unique_random_int(fixed_new_link_with_new_node,net,initial_number_of_nodes,fixed_new_link_with_new_node);
        for(k=0;k<fixed_new_link_with_new_node;k++){
            pr=run_to(neighbour[k],net);
            pr->degree++;
        }
        add_node(fixed_new_link_with_new_node,net);
        //degree_list(net);
    }
    degree_list(net,file);
}


void add_node(int degree,Network& net){
    node* pr=run_to(net.Num,net);
    pr->next=(node*)malloc(sizeof(node));
    pr->next->degree=degree;
    net.Num++;
}
node* run_to(int index,const Network& net){//index start from 1, 0 is the dummy head.
    node* pr;
    pr=net.dummy_head;
    if(index<=0) return pr;
    for(int i=1;i<=index;i++)
        pr=pr->next;
    return pr;
}
void degree_list(const Network& net,string file){//print
    node* pr;
    pr=net.dummy_head;
    ofstream out(file);
    out<<"Index\tdegree\n";
    for(int i=1;i<=net.Num;i++){
        pr=pr->next;
        out<<i<<"\t"<<pr->degree<<endl;
    }
    out<<"\n\n";
    out.close();out.clear();
    cout<<"\n";
}

int* unique_random_int(int n,Network net,int initial_number_of_nodes,int fixed_new_link_with_new_node,int new_seed){//[1,net.Num]
    static std::random_device rd;
    static std::mt19937_64 generator_3(rd());
    if(new_seed!=0)
        generator_3.seed(rd());
    static std::uniform_real_distribution<double> dr(0,1);
    int* number;
    int tmp;
    number=(int*)malloc(sizeof(int)*n);
    int j,k;
    int i=0;
    double p;

    //////
    //preference for network growth
    int q=0;
    p=dr(generator_3);
    //cout<<"all edges: "<<((net.Num-initial_number_of_nodes)*fixed_new_link_with_new_node+initial_number_of_nodes*(initial_number_of_nodes-1))<<endl;
    p=0.9999;
    for(q=1;p>=0;q++){
        //cout<<"run_to(q,net)->degree: "<<run_to(q,net)->degree<<endl;

        p=p-1.0*run_to(q,net)->degree /((net.Num-initial_number_of_nodes)*fixed_new_link_with_new_node*2+initial_number_of_nodes*(initial_number_of_nodes-1));
    }
    number[0]=q-1;
    for(i=1;i<n;i++){
        p=dr(generator_3);
        for(q=1;p>=0;q++){
            p=p-1.0*run_to(q,net)->degree /((net.Num-initial_number_of_nodes)*fixed_new_link_with_new_node+initial_number_of_nodes*(initial_number_of_nodes-1));
        }
        tmp=q-1;
        for(j=i;j>0 && number[j-1]>tmp;j--){
            number[j]=number[j-1];
        }
        if(j>0 && number[j-1]==tmp){
            for(k=j;k<i;k++){//drop the same number
                number[k]=number[k+1];
            }
            i--;
            continue;
        }
        number[j]=tmp;
    }
    /////

    /////
    //no preference for the network growth
    /*
    number[0]=int(dr(generator_3)*(high+1));
    for(i=1;i<n;i++){
        tmp=int(dr(generator_3)*(high+1));
        for(j=i;j>0 && number[j-1]>tmp;j--){
            number[j]=number[j-1];
        }
        if(j>0 && number[j-1]==tmp){
            for(k=j;k<i;k++){//drop the same number
                number[k]=number[k+1];
            }
            i--;
            continue;
        }
        number[j]=tmp;
    }
    */
    //no preference for the network growth
    //////

    /*
    cout<<"unique_random_list:";
    for(i=0;i<n;i++){
        cout<<number[i]<<",";
    }
    cout<<"\n";
    */

    return number;

}

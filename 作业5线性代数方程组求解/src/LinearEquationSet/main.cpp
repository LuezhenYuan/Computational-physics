//Get solution of linear equation set
/////////////////////////
//迭代法epsilon 可适当的小

//Compiler: gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04)
//Compile command: $ g++ -std=c++11 main.cpp -o program
//Enviroment: Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux
/////////////////////////////////////////////

//Algorithm
/*
# 高斯消去法
1. 对于线性方程组Ax=B, 输入系数矩阵A, 值向量B. 初始化x矩阵
2. 消元的数组更新顺序:
```
B(k) ...> B(i)
A(k,j) ...> A(i,j)
```
```
for k=1:(n-1)
	ColumnWatch(&A);//可以应用列主元素消去法
	B(k) =B(k)/B(k,k)
	for (j=k+1):n
		A(k,j)=A(k,j)/A(k,k)
		B(j)=B(j)-A(i,k)*B(k);
		for (i=k+1):n
			A(i,j)=A(i,j)-A(i,k)*A(k,j);

B(n)=B(n)/A(n,n)
```
3. 求方程组的解
```
for(i=n;i>=1;i--)
	x[i] = B[i];
	for(j=i+1;j<=n;j++)
		x[i]-=A(i,j)*x[j];
```

# 改进的列主元素消去法
原始的列主元素消去法需要将系数矩阵A的行互换(如第k和第j行).这通常需要申请一片暂时的空间,进行3*(n-k+1)次赋值操作.

改进的方法是将第j行加到第k行上去(A(k,k)同号时加,异号时减).方程组的解不变.

# 迭代法求方程组近似解
塞得尔迭代法.在同一矩阵下操作即可.
*/

//Author: Luezhen Yuan
//Last update: 20160320
/////////////////////////////////////////////
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
void Nothing(double A[],double B[],int n,int k){}//Nothing to do. Used as the default 'function object' in void Gauss(...)
void Gauss(const double cA[], const double cB[],int n,double* x,void ColumnWatch(double A[],double B[],int n,int k)=Nothing);//ColumnWatch is the 'function object'. The funciton can be run in void Gauss(...)
void ColumnPrincipleElimination(double A[],double B[],int n,int k);//Column Principle Elimination
void IterativeMethod(const double cA[], const double cB[],int n,double* x,double epsilon=0.00001);//Seidel iterative method
int main()
{
    //Ax=B. A should be a square matrix
    double A[]={10,-1,-2,2,1,-10,2,-1,1,1,-5,2,1,-2,2,-1};
    double B[]={4,-14,-10,2};
    //Case 2:
    //double A[]={2,3,1,1,1,1,1,-2,-1};
    //double B[]={9,4,-4};

    int n =sizeof(B)/sizeof(double);
    double* x;
    x= (double*)malloc(sizeof(double)*n);

    double* priA;double* priB;
    priA=&A[0];priB=&B[0];

    Gauss(priA,priB,n,x,ColumnPrincipleElimination);//Use the Column Principle Elimination
    Gauss(priA,priB,n,x);

    IterativeMethod(priA,priB,n,x,0.00001);
    free(x);
    return 0;
}


void Gauss(const double cA[], const double cB[],int n,double* x,void ColumnWatch(double A[],double B[],int n,int k) ){

    //cout<<"n:"<<n<<endl;//test
    double* A;A=(double*)malloc(sizeof(double)*n*n);
    double* B;B=(double*)malloc(sizeof(double)*n);
    for(int i=0;i<n*n;i++)A[i]=cA[i];
    for(int i=0;i<n;i++)B[i]=cB[i];
    int k=0,j=0,i=0;
    for(k=1;k<n;k++){
        ColumnWatch(A,B,n,k);//!!Here the function is called.
        //test

        B[k-1]/=A[n*(k-1)+ k-1 ];
        for(j=k+1;j<=n;j++){
            A[n*(k-1)+j-1]/=A[n*(k-1)+ k-1 ];
            B[j-1]-=A[n*(j-1)+k-1]*B[k-1];

            for(i=k+1;i<=n;i++){
                A[n*(i-1)+j-1]-=A[n*(i-1)+k-1]*A[n*(k-1)+j-1];
            }
        }
    }
    B[n-1]/=A[n*n-1];

    //Solution
    cout<<"Solution:\n";
    for(i=n;i>=1;i--){
        x[i-1]=B[i-1];
        for(j=i+1;j<=n;j++){
            x[i-1]-=A[n*(i-1)+j-1]*x[j-1];
        }

    }

    for(i=0;i<n;i++) cout<<x[i]<<",";
    cout<<"\n\n";
    free(A);free(B);A=NULL;B=NULL;

}

void ColumnPrincipleElimination(double A[],double B[],int n,int k){
    cout<<"Call Column Principle Elimination\n";
    double max=abs(A[n*(k-1)+k-1]);int j=k;

    //Find the max A[j][k]
    for(int i=k+1;i<=n;i++){
        if(abs(A[n*(i-1)+k-1])>max){
            max=abs(A[n*(i-1)+k-1]);
            j=i;
        }
    }
    int ind=1;
    if(A[n*(j-1)+k-1]*A[n*(k-1)+k-1]<0) ind=-1;

    //Add the jth row to kth's.
    for(int jp=1;jp<=n;jp++){
        //cout<<A[n*(k-1)+jp-1]<<"\n";
        A[n*(k-1)+jp-1]+=ind*A[n*(j-1)+jp-1];
        //cout<<A[n*(k-1)+jp-1]<<"\n";
    }
    //cout<<B[k-1]<<"\n";
    B[k-1]+=ind*B[j-1];
    //cout<<B[k-1]<<"\n";
}

void IterativeMethod(const double cA[], const double cB[],int n,double* x,double epsilon){
    cout<<"Iteration method\n";
    double* A;A=(double*)malloc(sizeof(double)*n*n);
    double* B;B=(double*)malloc(sizeof(double)*n);
    double* lastx;//The former solution x.
    lastx= (double*)malloc(sizeof(double)*n);
    for(int i=0;i<n*n;i++)A[i]=cA[i];
    for(int i=0;i<n;i++){
        B[i]=cB[i];
        x[i]=0;
        lastx[i]=100;
    }

    double maxdiff=100;
    int i=0,j=0;
    double tmp=0;
    int times=0;

    while(maxdiff>epsilon){
        times++;
        maxdiff=0;
        for(i=1;i<=n;i++){
            tmp=0;
            for(j=1;j<=n;j++)
                if(j!=i)
                    tmp+=A[n*(i-1)+j-1]*x[j-1];
            x[i-1]=B[i-1]/A[n*(i-1)+i-1] - 1/A[n*(i-1)+i-1] *tmp;
            //cout<<abs(lastx[i-1]-x[i-1])<<endl;
            if(abs(lastx[i-1]-x[i-1])>maxdiff) maxdiff=abs(lastx[i-1]-x[i-1]);
            lastx[i-1]=x[i-1];
        }
        //cout<<"maxdiff"<<maxdiff<<endl;
    }
    for(i=0;i<n;i++) cout<<x[i]<<",";
    cout<<"\nIteration times:"<<times<<endl;
    cout<<"\n\n";
}

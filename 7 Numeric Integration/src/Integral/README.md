# Adaptive Simpson's method
the first recursive adaptive algorithm for numerical integration to appear in print

```{c++}
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
```

# Adaptive Trapezoidal method
```{c++}
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
```

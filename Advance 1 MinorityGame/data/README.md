```
awk -F' ' 'BEGIN{} {if($2~/[0-9]/){print $0}}' nohup_All.txt
```
# read data to R
```{R}
a=matrix(,32*78,3);
for(m in 0:77){
str=paste("ZeroRatio_",m,".txt",sep="");
mydata=read.table(str,header=F);
i=1;j=1;

while(j<=32){
a[j+m*32,]=c(m,mean(mydata[i:(i+9999),1]),sd(mydata[i:(i+9999),1]))
i=i+10000;
j=j+1;
}
}
write.table(a,"MeanAndSd.txt")

```

# draw figure memory~Standard deviation
```
a=read.table("MeanAndSd.txt",header=F);
boxplot(a[1:(18*32),3]~(a[1:(18*32),1]+2),data=a)
m=a[1:(18*32),1]+2;

boxplot(a[1:(18*32),3]~m,data=a,xlab="memory",ylab="SD")
boxplot.stats(a[1:32,3])
plot(m,a[1:(18*32),3],xlab="memory",ylab="SD")
title(xlab="memory",ylab="SD")

b=matrix(,18,2)
for(i in 1:18){
b[i,]=c(i+1,mean(a[(32*i-31):(32*i),3]));
}
plot(b[,1],b[,2],xlab="memory",ylab="Average of SD")
```

# attendance changes
```
str=paste("ZeroRatio_",0,".txt",sep="");
mydata=read.table(str,header=F);

G=log(mydata[2:10000,1])-log(mydata[1:9999,1]);
d=density(G);
hist(G,freq=FALSE,main="")
rug(jitter(G),col="brown")
lines(d,col="blue",lwd=2)

G2=mydata[2:10000,1]-mydata[1:9999,1];
d2=density(G2);
plot(d2)

G3=abs(mydata[2:10000,1]-mydata[1:9999,1]);
d3=density(G3);
hist(G3,freq=FALSE,main="")
rug(jitter(G3),col="brown")
lines(d3,col="blue",lwd=2)

for(i in 1:8){
G=log(mydata[(i+1):10000,1])-log(mydata[1:(10000-i),1]);
d=density(G);
hist(G,freq=FALSE,main="",xlab=paste("G, dt=",i,sep=""))
rug(jitter(G),col="brown")
lines(d,col="blue",lwd=2)
}

for(i in 1:8){
G=log(mydata[(i*8*100+1):10000,1])-log(mydata[1:(10000-i*8*100),1]);
d=density(G);
hist(G,freq=FALSE,main="",xlab=paste("G, dt=",i*8*100,sep=""))
rug(jitter(G),col="brown")
lines(d,col="blue",lwd=2)
}

plot(mydata[9:10000,1],mydata[1:9992,1])
for(i in 1:8){
plot(mydata[(i*8+1):10000,1],mydata[1:(10000-i*8),1],xlab="N0(t)%",ylab=paste("N0(t+",i*8,")%",sep=""))
}
plot(mydata[4001:10000,1],mydata[1:6000,1],xlab="N0(t)%",ylab="N0(t+4000)%")
```
dt=8 is a cycle, and this pattern is kept well

# Anova

## Data frame construct
```
Input=read.table("Input.txt",header=F,sep=" ");
anova_data=matrix(,64*32,4);
j=1;
for(i in c(1,6,11,18,19:78)){
anova_data[(32*j-31):(j*32),1]=rep(Input[i,1],32);
anova_data[(32*j-31):(j*32),2]=rep(Input[i,2],32);
anova_data[(32*j-31):(j*32),3]=rep(Input[i,3],32);
anova_data[(32*j-31):(j*32),4]=a[(i*32-31):(i*32),3];
j=j+1;
}
anova_frame=data.frame(s=anova_data[,1],m=anova_data[,2],N=anova_data[,3],SD=anova_data[,4]);

anova_frame_factor=data.frame(s=factor(anova_data[,1]),m=factor(anova_data[,2]),N=factor(anova_data[,3]),SD=anova_data[,4]);
```

## Watch sample size and mean
```
table(anova_frame_factor$s,anova_frame_factor$m)
aggregate(anova_frame_factor$SD,by=list(anova_frame_factor$s),FUN=mean)
aggregate(anova_frame_factor$SD,by=list(anova_frame_factor$m),FUN=mean)
aggregate(anova_frame_factor$SD,by=list(anova_frame_factor$N),FUN=mean)

library(gplots)
plotmeans(SD~s,data=anova_frame_factor)
plotmeans(SD~m,data=anova_frame_factor)
plotmeans(SD~N,data=anova_frame_factor)
```
       2   7  12  19
  3  128 128 128 128
  6  128 128 128 128
  9  128 128 128 128
  12 128 128 128 128
  
  Group.1          x
1       3 0.04022659
2       6 0.05033104
3       9 0.05613580
4      12 0.05734526

  Group.1          x
1       2 0.10267228
2       7 0.03262416
3      12 0.03404817
4      19 0.03469407

  Group.1          x
1     101 0.06208720
2     201 0.04894294
3     301 0.04418343
4     401 0.04882511

## Anova
```
anova_frame_aov=aov(SD~s*m*N,data=anova_frame)
summary(anova_frame_aov)

anova_frame_factor_aov=aov(SD~s*m*N,data=anova_frame_factor)
summary(anova_frame_factor_aov)
```
              Df Sum Sq Mean Sq  F value   Pr(>F)    
s              3 0.0938  0.0313   56.751  < 2e-16 ***
m              3 1.8232  0.6077 1103.382  < 2e-16 ***
N              3 0.0913  0.0304   55.264  < 2e-16 ***
s:m            9 0.1256  0.0140   25.347  < 2e-16 ***
s:N            9 0.0255  0.0028    5.152 6.25e-07 ***
m:N            9 0.0822  0.0091   16.573  < 2e-16 ***
s:m:N         27 0.0745  0.0028    5.008 1.01e-15 ***
Residuals   1984 1.0928  0.0006                      
---
Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

## Tuckey multiple comparisons
```
par(las=1)
anova_frame_factor_aov_Tukey=TukeyHSD(anova_frame_factor_aov,which="s");
plot(anova_frame_factor_aov_Tukey)

anova_frame_factor_aov_Tukey=TukeyHSD(anova_frame_factor_aov,which="m");
plot(anova_frame_factor_aov_Tukey)

anova_frame_factor_aov_Tukey=TukeyHSD(anova_frame_factor_aov,which="N");
plot(anova_frame_factor_aov_Tukey)

```

## Quantitative factor
three factor:
s is quantitative(3,6,9,12)
m is quantitative(2,7,12)
N is quantitative(101,201,301,401)

Actually, m is (2,7,12,19), However, the intervals between them are not equal, so I drop the 19 level.

4 level:
-0.6708 -0.2236 0.2236 0.6708
0.5 -0.5 -0.5 0.5
-0.2236 0.6708 -0.6708 0.2236

3 level:
-0.707107 0 0.707107
0.408248 -0.816497 0.408248

```
anova_frame_factor_m2712=anova_frame_factor[which(anova_frame_factor[,2]!=19),];
anova_frame_factor_m2712[,1]

quan_4=matrix(,3,4)
quan_4[1,]=c(-0.6708,-0.2236,0.2236,0.6708)
quan_4[2,]=c(0.5,-0.5,-0.5,0.5)
quan_4[3,]=c(-0.2236,0.6708,-0.6708,0.2236)
quan_3=matrix(,2,3)
quan_3[1,]=c(-0.707107,0,0.707107)
quan_3[2,]=c(0.408248,-0.816497,0.408248)

anova_frame_factor_m2712_quan=matrix(,1536,9);
for(i in 1:4){#s
  for(j in 1:4){#N
    for(k in 1:3){#m
      # The (i-1)*12*32+(j-1)*3*32+(k-1)*32+1 row
      for(p in 1:32){
        # The (i-1)*12*32+(j-1)*3*32+(k-1)*32+p row
        anova_frame_factor_m2712_quan[(i-1)*12*32+(j-1)*3*32+(k-1)*32+p,]=c(quan_4[1,i],quan_4[2,i],quan_4[3,i],quan_3[1,k],quan_3[2,k],quan_4[1,j],quan_4[2,j],quan_4[3,j],anova_frame_factor_m2712[(i-1)*12*32+(j-1)*3*32+(k-1)*32+p,4])
      }
    }
  }
}
anova_frame_factor_m2712_quan_frame=data.frame(s_l=anova_frame_factor_m2712_quan[,1],s_q=anova_frame_factor_m2712_quan[,2],s_c=anova_frame_factor_m2712_quan[,3],m_l=anova_frame_factor_m2712_quan[,4],m_q=anova_frame_factor_m2712_quan[,5],N_l=anova_frame_factor_m2712_quan[,6],N_q=anova_frame_factor_m2712_quan[,7],N_c=anova_frame_factor_m2712_quan[,8],SD=anova_frame_factor_m2712_quan[,9])
```

### Anova

```
anova_frame_factor_m2712_quan_frame_aov=aov(SD~s_l*s_q*s_c*m_l*m_q*N_l*N_q*N_c,data=anova_frame_factor_m2712_quan_frame)
summary(anova_frame_factor_m2712_quan_frame_aov)
```
              Df Sum Sq Mean Sq  F value   Pr(>F)    
s_l            1 0.1115  0.1115  151.820  < 2e-16 ***
s_q            1 0.0135  0.0135   18.422 1.88e-05 ***
s_c            1 0.0000  0.0000    0.005 0.943710    
m_l            1 1.2056  1.2056 1641.647  < 2e-16 ***
m_q            1 0.4359  0.4359  593.579  < 2e-16 ***
N_l            1 0.0202  0.0202   27.538 1.76e-07 ***
N_q            1 0.0391  0.0391   53.182 4.92e-13 ***
N_c            1 0.0002  0.0002    0.261 0.609184    
s_l:m_l        1 0.0773  0.0773  105.195  < 2e-16 ***
s_q:m_l        1 0.0147  0.0147   19.960 8.50e-06 ***
s_c:m_l        1 0.0000  0.0000    0.037 0.847962    
s_l:m_q        1 0.0003  0.0003    0.349 0.554699    
s_q:m_q        1 0.0021  0.0021    2.854 0.091331 .  
s_c:m_q        1 0.0001  0.0001    0.149 0.699832    
s_l:N_l        1 0.0049  0.0049    6.730 0.009574 ** 
s_q:N_l        1 0.0052  0.0052    7.077 0.007892 ** 
s_c:N_l        1 0.0115  0.0115   15.655 7.96e-05 ***
m_l:N_l        1 0.0397  0.0397   54.070 3.18e-13 ***
m_q:N_l        1 0.0019  0.0019    2.616 0.106017    
s_l:N_q        1 0.0074  0.0074   10.048 0.001556 ** 
s_q:N_q        1 0.0008  0.0008    1.024 0.311633    
s_c:N_q        1 0.0037  0.0037    5.034 0.025003 *  
m_l:N_q        1 0.0164  0.0164   22.375 2.46e-06 ***
m_q:N_q        1 0.0083  0.0083   11.348 0.000775 ***
s_l:N_c        1 0.0001  0.0001    0.173 0.677240    
s_q:N_c        1 0.0002  0.0002    0.320 0.571635    
s_c:N_c        1 0.0001  0.0001    0.148 0.700806    
m_l:N_c        1 0.0017  0.0017    2.326 0.127474    
m_q:N_c        1 0.0003  0.0003    0.396 0.529338    
s_l:m_l:N_l    1 0.0054  0.0054    7.410 0.006560 ** 
s_q:m_l:N_l    1 0.0057  0.0057    7.703 0.005583 ** 
s_c:m_l:N_l    1 0.0192  0.0192   26.084 3.69e-07 ***
s_l:m_q:N_l    1 0.0010  0.0010    1.370 0.242012    
s_q:m_q:N_l    1 0.0008  0.0008    1.145 0.284835    
s_c:m_q:N_l    1 0.0076  0.0076   10.367 0.001310 ** 
s_l:m_l:N_q    1 0.0119  0.0119   16.201 5.98e-05 ***
s_q:m_l:N_q    1 0.0017  0.0017    2.310 0.128755    
s_c:m_l:N_q    1 0.0048  0.0048    6.570 0.010468 *  
s_l:m_q:N_q    1 0.0044  0.0044    5.952 0.014816 *  
s_q:m_q:N_q    1 0.0010  0.0010    1.412 0.234957    
s_c:m_q:N_q    1 0.0013  0.0013    1.727 0.189048    
s_l:m_l:N_c    1 0.0002  0.0002    0.313 0.575798    
s_q:m_l:N_c    1 0.0003  0.0003    0.473 0.491796    
s_c:m_l:N_c    1 0.0003  0.0003    0.392 0.531262    
s_l:m_q:N_c    1 0.0001  0.0001    0.130 0.718460    
s_q:m_q:N_c    1 0.0001  0.0001    0.158 0.691405    
s_c:m_q:N_c    1 0.0002  0.0002    0.261 0.609191    
Residuals   1488 1.0927  0.0007                      
---
Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

#### Remove insignificant effect

```
anova_frame_factor_m2712_quan_frame_aov_sig=aov(SD~s_l+s_q+m_l+m_q+N_l+N_q+s_l:m_l+s_q:m_l+s_l:N_l+s_q:N_l+s_c:N_l+m_l:N_l+s_l:N_q+s_c:N_q+m_l:N_q+m_q:N_q+s_l:m_l:N_l+s_q:m_l:N_l+s_c:m_l:N_l+s_c:m_q:N_l+s_l:m_l:N_q+s_c:m_l:N_q+s_l:m_q:N_q,data=anova_frame_factor_m2712_quan_frame)
summary(anova_frame_factor_m2712_quan_frame_aov_sig)
```

              Df Sum Sq Mean Sq  F value   Pr(>F)    
s_l            1 0.1115  0.1115  152.188  < 2e-16 ***
s_q            1 0.0135  0.0135   18.467 1.84e-05 ***
m_l            1 1.2056  1.2056 1645.622  < 2e-16 ***
m_q            1 0.4359  0.4359  595.016  < 2e-16 ***
N_l            1 0.0202  0.0202   27.605 1.70e-07 ***
N_q            1 0.0391  0.0391   53.311 4.58e-13 ***
s_l:m_l        1 0.0773  0.0773  105.449  < 2e-16 ***
s_q:m_l        1 0.0147  0.0147   20.009 8.29e-06 ***
s_l:N_l        1 0.0049  0.0049    6.746 0.009486 ** 
s_q:N_l        1 0.0052  0.0052    7.094 0.007816 ** 
N_l:s_c        1 0.0115  0.0115   15.693 7.80e-05 ***
m_l:N_l        1 0.0397  0.0397   54.201 2.96e-13 ***
s_l:N_q        1 0.0074  0.0074   10.072 0.001535 ** 
N_q:s_c        1 0.0037  0.0037    5.046 0.024826 *  
m_l:N_q        1 0.0164  0.0164   22.429 2.38e-06 ***
m_q:N_q        1 0.0083  0.0083   11.375 0.000763 ***
s_l:m_l:N_l    1 0.0054  0.0054    7.428 0.006494 ** 
s_q:m_l:N_l    1 0.0057  0.0057    7.721 0.005525 ** 
m_l:N_l:s_c    1 0.0192  0.0192   26.147 3.57e-07 ***
m_q:N_l:s_c    1 0.0076  0.0076   10.392 0.001292 ** 
s_l:m_l:N_q    1 0.0119  0.0119   16.240 5.86e-05 ***
m_l:N_q:s_c    1 0.0048  0.0048    6.586 0.010374 *  
s_l:m_q:N_q    1 0.0044  0.0044    5.967 0.014694 *  
Residuals   1512 1.1077  0.0007                      
---
Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

### Regression approach to factorial designs
SD=s_l+s_q+s_c+...
```
anova_frame_factor_m2712_quan_frame_aov_sig_reg=lm(SD~s_l+s_q+m_l+m_q+N_l+N_q+s_l:m_l+s_q:m_l+s_l:N_l+s_q:N_l+s_c:N_l+m_l:N_l+s_l:N_q+s_c:N_q+m_l:N_q+m_q:N_q+s_l:m_l:N_l+s_q:m_l:N_l+s_c:m_l:N_l+s_c:m_q:N_l+s_l:m_l:N_q+s_c:m_l:N_q+s_l:m_q:N_q,data=anova_frame_factor_m2712_quan_frame)
summary(anova_frame_factor_m2712_quan_frame_aov_sig_reg)
```

Residuals:
      Min        1Q    Median        3Q       Max 
-0.084555 -0.007685 -0.000936  0.002123  0.185289 

Coefficients:
              Estimate Std. Error t value Pr(>|t|)    
(Intercept)  0.0564482  0.0006906  81.736  < 2e-16 ***
s_l          0.0170400  0.0013813  12.336  < 2e-16 ***
s_q         -0.0059355  0.0013812  -4.297 1.84e-05 ***
m_l         -0.0485246  0.0011962 -40.566  < 2e-16 ***
m_q          0.0291784  0.0011962  24.393  < 2e-16 ***
N_l         -0.0072572  0.0013813  -5.254 1.70e-07 ***
N_q          0.0100850  0.0013812   7.301 4.58e-13 ***
s_l:m_l     -0.0245675  0.0023924 -10.269  < 2e-16 ***
s_q:m_l      0.0107012  0.0023924   4.473 8.29e-06 ***
s_l:N_l      0.0071755  0.0027626   2.597 0.009486 ** 
s_q:N_l     -0.0073580  0.0027625  -2.663 0.007816 ** 
N_l:s_c     -0.0109439  0.0027626  -3.961 7.80e-05 ***
m_l:N_l     -0.0176134  0.0023924  -7.362 2.96e-13 ***
s_l:N_q      0.0087675  0.0027625   3.174 0.001535 ** 
N_q:s_c     -0.0062056  0.0027625  -2.246 0.024826 *  
m_l:N_q     -0.0113301  0.0023924  -4.736 2.38e-06 ***
m_q:N_q      0.0080688  0.0023924   3.373 0.000763 ***
s_l:m_l:N_l -0.0130416  0.0047850  -2.726 0.006494 ** 
s_q:m_l:N_l  0.0132959  0.0047849   2.779 0.005525 ** 
m_l:N_l:s_c  0.0244677  0.0047850   5.113 3.57e-07 ***
m_q:N_l:s_c -0.0154256  0.0047850  -3.224 0.001292 ** 
s_l:m_l:N_q -0.0192824  0.0047849  -4.030 5.86e-05 ***
m_l:N_q:s_c  0.0122795  0.0047849   2.566 0.010374 *  
s_l:m_q:N_q  0.0116877  0.0047849   2.443 0.014694 *  
---
Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

Residual standard error: 0.02707 on 1512 degrees of freedom
Multiple R-squared:  0.6518,	Adjusted R-squared:  0.6465 
F-statistic: 123.1 on 23 and 1512 DF,  p-value: < 2.2e-16

#### try simple model
```
anova_frame_factor_m2712_quan_frame_aov_sig_reg_simple=lm(SD~s_l+s_q+m_l+m_q+N_l+N_q,data=anova_frame_factor_m2712_quan_frame)
summary(anova_frame_factor_m2712_quan_frame_aov_sig_reg_simple)
```
Coefficients:
              Estimate Std. Error t value Pr(>|t|)    
(Intercept)  0.0564482  0.0007598  74.295  < 2e-16 ***
s_l          0.0170400  0.0015196  11.213  < 2e-16 ***
s_q         -0.0059355  0.0015196  -3.906 9.79e-05 ***
m_l         -0.0485246  0.0013160 -36.873  < 2e-16 ***
m_q          0.0291784  0.0013160  22.172  < 2e-16 ***
N_l         -0.0072572  0.0015196  -4.776 1.96e-06 ***
N_q          0.0100850  0.0015196   6.637 4.44e-11 ***
---
Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

Residual standard error: 0.02978 on 1529 degrees of freedom
Multiple R-squared:  0.5739,	Adjusted R-squared:  0.5722 
F-statistic: 343.2 on 6 and 1529 DF,  p-value: < 2.2e-16

#### stepwise method(reject this work)

```
library(MASS)
anova_frame_factor_m2712_quan_frame_aov_reg_1=lm(SD~s_l*s_q*s_c*m_l*m_q*N_l*N_q*N_c,data=anova_frame_factor_m2712_quan_frame)
stepAIC(anova_frame_factor_m2712_quan_frame_aov_reg_1,direction="both",trace=FALSE,steps=10000)
```
lm(formula = SD ~ s_l + s_q + s_c + m_l + m_q + N_l + N_q + N_c + 
    s_l:m_l + s_q:m_l + s_c:m_l + s_l:m_q + s_q:m_q + s_c:m_q + 
    s_l:N_l + s_q:N_l + s_c:N_l + m_l:N_l + m_q:N_l + s_l:N_q + 
    s_q:N_q + s_c:N_q + m_l:N_q + m_q:N_q + m_l:N_c + s_l:m_l:N_l + 
    s_q:m_l:N_l + s_c:m_l:N_l + s_c:m_q:N_l + s_l:m_l:N_q + s_q:m_l:N_q + 
    s_c:m_l:N_q + s_l:m_q:N_q, data = anova_frame_factor_m2712_quan_frame)

Coefficients:
(Intercept)          s_l          s_q          s_c          m_l          m_q          N_l  
  5.645e-02    1.704e-02   -5.936e-03   -9.766e-05   -4.852e-02    2.918e-02   -7.257e-03  
        N_q          N_c      s_l:m_l      s_q:m_l      s_c:m_l      s_l:m_q      s_q:m_q  
  1.008e-02    7.072e-04   -2.457e-02    1.070e-02   -4.593e-04    1.415e-03   -4.047e-03  
    s_c:m_q      s_l:N_l      s_q:N_l      s_c:N_l      m_l:N_l      m_q:N_l      s_l:N_q  
  9.237e-04    7.175e-03   -7.358e-03   -1.094e-02   -1.761e-02    3.874e-03    8.768e-03  
    s_q:N_q      s_c:N_q      m_l:N_q      m_q:N_q      m_l:N_c  s_l:m_l:N_l  s_q:m_l:N_l  
 -2.799e-03   -6.206e-03   -1.133e-02    8.069e-03   -3.653e-03   -1.304e-02    1.330e-02  
s_c:m_l:N_l  s_c:m_q:N_l  s_l:m_l:N_q  s_q:m_l:N_q  s_c:m_l:N_q  s_l:m_q:N_q  
  2.447e-02   -1.543e-02   -1.928e-02    7.281e-03    1.228e-02    1.169e-02  

```
anova_frame_factor_m2712_quan_frame_aov_reg_step=lm(formula = SD ~ s_l + s_q + s_c + m_l + m_q + N_l + N_q + N_c + 
    s_l:m_l + s_q:m_l + s_c:m_l + s_l:m_q + s_q:m_q + s_c:m_q + 
    s_l:N_l + s_q:N_l + s_c:N_l + m_l:N_l + m_q:N_l + s_l:N_q + 
    s_q:N_q + s_c:N_q + m_l:N_q + m_q:N_q + m_l:N_c + s_l:m_l:N_l + 
    s_q:m_l:N_l + s_c:m_l:N_l + s_c:m_q:N_l + s_l:m_l:N_q + s_q:m_l:N_q + 
    s_c:m_l:N_q + s_l:m_q:N_q, data = anova_frame_factor_m2712_quan_frame)
summary(anova_frame_factor_m2712_quan_frame_aov_reg_step)
```
Residuals:
      Min        1Q    Median        3Q       Max 
-0.088888 -0.006155 -0.000828  0.001272  0.181752 

Coefficients:
              Estimate Std. Error t value Pr(>|t|)    
(Intercept)  5.645e-02  6.902e-04  81.790  < 2e-16 ***
s_l          1.704e-02  1.380e-03  12.345  < 2e-16 ***
s_q         -5.936e-03  1.380e-03  -4.300 1.82e-05 ***
s_c         -9.766e-05  1.380e-03  -0.071 0.943606    
m_l         -4.852e-02  1.195e-03 -40.593  < 2e-16 ***
m_q          2.918e-02  1.195e-03  24.409  < 2e-16 ***
N_l         -7.257e-03  1.380e-03  -5.257 1.67e-07 ***
N_q          1.008e-02  1.380e-03   7.306 4.44e-13 ***
N_c          7.072e-04  1.380e-03   0.512 0.608516    
s_l:m_l     -2.457e-02  2.391e-03 -10.276  < 2e-16 ***
s_q:m_l      1.070e-02  2.391e-03   4.476 8.18e-06 ***
s_c:m_l     -4.593e-04  2.391e-03  -0.192 0.847681    
s_l:m_q      1.415e-03  2.391e-03   0.592 0.553960    
s_q:m_q     -4.047e-03  2.391e-03  -1.693 0.090727 .  
s_c:m_q      9.237e-04  2.391e-03   0.386 0.699299    
s_l:N_l      7.175e-03  2.761e-03   2.599 0.009440 ** 
s_q:N_l     -7.358e-03  2.761e-03  -2.665 0.007776 ** 
s_c:N_l     -1.094e-02  2.761e-03  -3.964 7.72e-05 ***
m_l:N_l     -1.761e-02  2.391e-03  -7.367 2.87e-13 ***
m_q:N_l      3.874e-03  2.391e-03   1.620 0.105367    
s_l:N_q      8.768e-03  2.761e-03   3.176 0.001525 ** 
s_q:N_q     -2.799e-03  2.761e-03  -1.014 0.310731    
s_c:N_q     -6.206e-03  2.761e-03  -2.248 0.024733 *  
m_l:N_q     -1.133e-02  2.391e-03  -4.739 2.35e-06 ***
m_q:N_q      8.069e-03  2.391e-03   3.375 0.000757 ***
m_l:N_c     -3.653e-03  2.391e-03  -1.528 0.126765    
s_l:m_l:N_l -1.304e-02  4.782e-03  -2.727 0.006460 ** 
s_q:m_l:N_l  1.330e-02  4.782e-03   2.781 0.005495 ** 
s_c:m_l:N_l  2.447e-02  4.782e-03   5.117 3.51e-07 ***
s_c:m_q:N_l -1.543e-02  4.782e-03  -3.226 0.001283 ** 
s_l:m_l:N_q -1.928e-02  4.782e-03  -4.033 5.80e-05 ***
s_q:m_l:N_q  7.281e-03  4.782e-03   1.523 0.128043    
s_c:m_l:N_q  1.228e-02  4.782e-03   2.568 0.010325 *  
s_l:m_q:N_q  1.169e-02  4.782e-03   2.444 0.014630 *  
---
Signif. codes:  0 ‘***’ 0.001 ‘**’ 0.01 ‘*’ 0.05 ‘.’ 0.1 ‘ ’ 1

Residual standard error: 0.02705 on 1502 degrees of freedom
Multiple R-squared:  0.6546,	Adjusted R-squared:  0.647 
F-statistic: 86.26 on 33 and 1502 DF,  p-value: < 2.2e-16

Not good, may be the steps time is not enough, reject this work!

#### Cross Validation
```
shrinkage = function(fit,k=10){
  require(bootstrap)
  
  theta.fit=function(x,y){lsfit(x,y)}
  theta.predict=function(fit,x){cbind(1,x)%*%fit$coef}
  
  x=fit$model[,2:ncol(fit$model)]
  y=fit$model[,1]
  
  results=crossval(x,y,theta.fit,theta.predict,ngroup=k)
  r2=cor(y,fit$fitted.values)^2
  r2cv=cor(y,results$cv.fit)^2
  cat("Original R-square=",r2,"\n")
  cat(k,"Fold Cross-Validated R-square=",r2cv,"\n")
  cat("Change=",r2-r2cv,"\n")
}
```

```
shrinkage(anova_frame_factor_m2712_quan_frame_aov_sig_reg)
```
Original R-square= 0.6518378 
10 Fold Cross-Validated R-square= 0.5704969 
Change= 0.08134088

```
shrinkage(anova_frame_factor_m2712_quan_frame_aov_sig_reg_simple)
```
Original R-square= 0.5738707 
10 Fold Cross-Validated R-square= 0.5705647 
Change= 0.003306007 

```
anova_frame_factor_m2712_quan_frame_aov_sig_reg_simple$coefficients
```
 (Intercept)          s_l          s_q          m_l          m_q          N_l          N_q 
 0.056448216  0.017039993 -0.005935532 -0.048524557  0.029178373 -0.007257206  0.010084956 

#### stepwise method(reject this work)
```
library(MASS)
stepAIC(anova_frame_factor_m2712_quan_frame_aov_sig_reg_simple,direction="both",trace=FALSE)

```

lm(formula = SD ~ s_l + s_q + m_l + m_q + N_l + N_q, data = anova_frame_factor_m2712_quan_frame)

Coefficients:
(Intercept)          s_l          s_q          m_l          m_q          N_l          N_q  
   0.056448     0.017040    -0.005936    -0.048525     0.029178    -0.007257     0.010085  

Just the original model

#### Analysis the model(from s,m,N to s_l, s_q,...)
```
X_4=function(x,m,D){
  lambda=c(2,1,10.0/3);
  k=4;
  C=c(20,4,20);
  return(c(lambda[1]*(x-m)/D/sqrt(C[1]),lambda[2]*(((x-m)/D)^2-(k^2-1)/12)/sqrt(C[2]),lambda[3]*(((x-m)/D)^3-((x-m)/D)*(3*k^2-7)/20)*sqrt(C[3])));
}
X_3=function(x,m,D){
  lambda=c(1,3);
  k=3;
  C=c(2,6);
  return(c(lambda[1]*(x-m)/D/sqrt(C[1]),lambda[2]*(((x-m)/D)^2-(k^2-1)/12)/sqrt(C[2])));
}

SD_pre=function(s,m,N){
  a=X_4(s,7.5,3);
  b=X_3(m,7,5);
  c=X_4(N,251,100);
  s_l=a[1];
  s_q=a[2];
  s_c=a[3];
  m_l=b[1];
  m_q=b[2];
  N_l=c[1];
  N_q=c[2];
  return(0.056448216+0.017039993*s_l-0.005935532*s_q-0.048524557*m_l+0.029178373*m_q-0.007257206*N_l+0.010084956*N_q);
}
library(scatterplot3d)
par(las=1)
for(N in seq(51,401,50)){
  SD_pre_data=matrix(,19*19,3);
  i=1;
  for(s in 2:20){
    for(m in 2:20){
        SD_pre_data[i,]=c(s,m,SD_pre(s,m,N));
        i=i+1;
    }
  }
  scatterplot3d(SD_pre_data[,1],SD_pre_data[,2],SD_pre_data[,3],main=paste("N=",N,sep=""),xlab="s",ylab="m",zlab="SD")
}
```
Conclusion: provide around 8 datas record is good for bar boss.

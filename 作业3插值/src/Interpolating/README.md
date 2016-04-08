# 算法
```{c++}
Input: x0 xn n
Output: matrix of x,predicted value y,the real value yreal
//n+1个点,包括x0,x1
calculate xi,yi,and store in the vector x, and y
//由于曲线是由散点连线得到,因此可以输出大量散点,而不是输出函数
for xt=x0:xn(sample 100 points)
	result=0;
	for j=0:n
		Aj=1;
		for i=0:n
			if i!=j
				Aj*=(xt-x[i])/(x[j]-x[i])
		result+=Aj*y[j]
	print xt,result,yreal
```

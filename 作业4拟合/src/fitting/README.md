# Reuse of the second assignments' code
1. In the second assignments, I use Object-oriented programming(OOP) to construct a class. In the class _SimpleStatisticsProject_, I can generate a dataset using random numbers.
2. I'd like to continue using the OOP(the class _SimpleStatisticsProject_) in this assignment.
3. To make the code tidy, I separate the code into several files.

# Algorithm
```
1. Generate standard deviation for average~N
2. Transform the data

ind = 0;
if(y(N) = a e^{bN})
	Y' = lny;N'= N;ind = 1;//lnY = lna + bx
else if(y(N) = a N^b)
	Y' = lny; N' = lnN;ind = 2//lnY = lna + blnN

3. Several average calculation: \bar{x}, \bar{y}, \bar{xy}, \bar{x^2}, n=length(Y');
4. Linear correlation coefficient:

ab=0;a2=0;b2=0;
for i=1:n:
	a = (x_i-\bar{x});
	b = (y_i-\bar{y});
	ab + = a*b;
	a2 += a*a;b2 += b*b;
end for
r = a*b/(a2 * b2)^0.5

5. Linear fitting:

A1 = (\bar{xy} - \bar{x} * \bar{y})/(\bar{x^2} - \bar{x}^2);
A0 = \bar{y} - A1 * \bar{x};

tmp = 0;
for i = 1:n:
	tmp += (yi - A0 - A1 * xi)^2;
sigma = (1/(n-2) * tmp)^0.5;//standard deviation
sigmaA0 = sigma * (\bar{x^2}/(n*\bar{x^2} - \bar{x}^2 ) )^0.5;
sigmaA1 = sigma * (1/(n*\bar{x^2} - \bar{x}^2 ) )^0.5

6. Transform back
a = e^A0;b=A1;

if(ind == 1 or ind == 2)
	y'pred = e(A0 + A1*N');//predicted y
	ypred = e^{y'pred};
	cout<< N<<y<<ypred;
```


# Simulation design
1. 3,2:19,101
2. 4*4*4
## Agents are homogeneous
s strategies hold for one agent
m size of memory used by one agent
N Number of agents

Decision: "0" go to the bar, "1" stay at home

# Boss of the bar: Low standard deviation is good

## How many records provided is good?
Test cases
3 2 101 -1 10000 32 -1
3 3 101 -1 10000 32 -1
3 4 101 -1 10000 32 -1
3 5 101 -1 10000 32 -1
3 6 101 -1 10000 32 -1
3 7 101 -1 10000 32 -1
3 8 101 -1 10000 32 -1
3 9 101 -1 10000 32 -1
3 10 101 -1 10000 32 -1
3 11 101 -1 10000 32 -1
3 12 101 -1 10000 32 -1
3 13 101 -1 10000 32 -1
3 14 101 -1 10000 32 -1
3 15 101 -1 10000 32 -1
3 16 101 -1 10000 32 -1
3 17 101 -1 10000 32 -1
3 18 101 -1 10000 32 -1
3 19 101 -1 10000 32 -1

Is this finding true for other cases(other s, N)?

### ANOVA
SD = s + m + N + s*m + s*N + m*N + s*m*N
aov(SD~s*m*N)

result: Tukey multiple comperisons

#### quantitative factor
simple model, cross validation

result: 1. Function to predict the SD 2. confirm that history record around 7 is good.

## How to predict the number of customers tonight?
8 days cycle pattern



# Directories
	\data output data. Data processing and analysis is done in linux command line tools and R. 
	\doc report.pdf
	\result Figures drawn from the data analysis(Anova, linear regression). Use R.
	\src Source code
	README.md This file

# Software Version

## Operating System
```{bash} 
uname -a
```
	Linux luezhen-ThinkPad-Edge-E431 3.16.0-37-generic #51~14.04.1-Ubuntu SMP Wed May 6 15:23:14 UTC 2015 x86_64 x86_64 x86_64 GNU/Linux

## GCC (c++) Compiler
```{bash} 
gcc -v
```
	Using built-in specs.
	COLLECT_GCC=gcc
	COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/4.8/lto-wrapper
	Target: x86_64-linux-gnu
	Configured with: ../src/configure -v --with-pkgversion='Ubuntu 4.8.4-2ubuntu1~14.04' --with-bugurl=file:///usr/share/doc/gcc-4.8/README.Bugs --enable-languages=c,c++,java,go,d,fortran,objc,obj-c++ --prefix=/usr --program-suffix=-4.8 --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --with-gxx-include-dir=/usr/include/c++/4.8 --libdir=/usr/lib --enable-nls --with-sysroot=/ --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --enable-gnu-unique-object --disable-libmudflap --enable-plugin --with-system-zlib --disable-browser-plugin --enable-java-awt=gtk --enable-gtk-cairo --with-java-home=/usr/lib/jvm/java-1.5.0-gcj-4.8-amd64/jre --enable-java-home --with-jvm-root-dir=/usr/lib/jvm/java-1.5.0-gcj-4.8-amd64 --with-jvm-jar-dir=/usr/lib/jvm-exports/java-1.5.0-gcj-4.8-amd64 --with-arch-directory=amd64 --with-ecj-jar=/usr/share/java/eclipse-ecj.jar --enable-objc-gc --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --with-tune=generic --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
	Thread model: posix
	gcc version 4.8.4 (Ubuntu 4.8.4-2ubuntu1~14.04) 

## Texmaker - a latex editor 
	Texmaker 4.1
	(compiled with Qt 4.8.4 and Poppler 0.24.3)
	Copyright (c) 2003-2013 by Pascal Brachet

## R version 3.2.4

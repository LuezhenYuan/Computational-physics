# 程序编译的注意事项
可行的编译方法:  
```{bash}
$ g++ -std=c++11 -o try main.cpp
```
注意：需要编译器开启支持c++11标准的选项！
Attention: Have your compiler follow the c++11 ISO C++ language standard [-std=c++11]
You can modify your "Global compiler settings": find the "c++11" like term and allow it!

# 程序流程
1. 产生随机数,形成数据集(输入N,n,输出data,并输出到文件out(文件名str,str_dataset.txt))
2. 画直方图(输入data,s,输出频数表str_freqtab.txt)
3. 计算基本统计量(输入data,输出平均值avera,平均值的标准偏差avestandevia)
4. 错误值剔除(输入data,输出原始data到文件中(可选),data变量原处修改)


# 随机数发生器介绍
```{c++}
#include <random> //random-number library 
    std::default_random_engine dre;
    std::uniform_real_distribution<double> dr(0,1);
    for(int i=0;i<8;i++){
        cout<<dr(dre)<<"\n";
    }
    cout<<"\n";
```
`std::default_random_engine`比较简单
`std::random_device` [is true random number generator][1], 产生 a uniformly-distributed integer.(在某些操作系统\编译器,may be implemented in terms of a pseudo-random number engine if a non-deterministic source (e.g. a hardware device) is not available to the implementation. )

GCC does not implement rd.entropy() correctly - it always returns 0
```{c++}
    std::random_device rd;
    cout<<"See if the random_device is true random number generator(if not 0, then is true):";
    cout<<rd.entropy()<<endl;
    std::mt19937_64 rseed(rd());
    std::uniform_real_distribution<double> dr(0,1);
    for(int i=0;i<8;i++){
        cout<<dr(rseed)<<"\n";
    }
    cout<<"\n";
```

[A random seed (or seed state, or just seed) is a number (or vector) used to initialize a pseudorandom number generator. For a seed to be used in a pseudorandom number generator, it does not need to be random. The choice of a good random seed is crucial in the field of computer security. When a secret encryption key is pseudorandomly generated, having the seed will allow one to obtain the key.][2]  


[1]: http://www.cplusplus.com/reference/random/random_device/ cplusplus reference random_device
[2]: https://en.wikipedia.org/wiki/Random_seed Wikipedia random seed

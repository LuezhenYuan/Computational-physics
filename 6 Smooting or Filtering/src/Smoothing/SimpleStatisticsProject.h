//This class is a practice in basic statistic analysis of data

/////////////////
//Constrain for parameter:
//N无,n>=1000较好,s>=10(不宜过小)
/////////////////
//# 类的功能
//1. 产生随机数,形成数据集(输入N,n,输出data,并输出到文件out(文件名str,str_dataset.txt))
//2. 画直方图(输入data,s,输出频数表str_freqtab.txt)
//3. 计算基本统计量(输入data,输出平均值avera,平均值的标准偏差avestandevia)
//4. 错误值剔除(输入data,输出原始data到文件中(可选),data变量原处修改)
////////////////


//Author: Luezhen Yuan
//Last update: 20160313
/////////////////////////////////////////////
#ifndef SIMPLESTATISTICSPROJECT_H_INCLUDED
#define SIMPLESTATISTICSPROJECT_H_INCLUDED

#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class SimpleStatisticsProject{
protected:
    int m_N,m_n;
    vector<double> m_data;
    ofstream m_out;
    string m_str;
    int m_s;

public:
    double avera,avestandevia;
    SimpleStatisticsProject():m_N(3),m_n(1000),m_data(),m_out(),m_str("result"),m_s(10),avera(0),avestandevia(0){}
    SimpleStatisticsProject(int N,int n,string str,int s):m_N(N),m_n(n),m_data(m_n),m_out(),m_str(str),m_s(s),avera(0),avestandevia(0){}
    ~SimpleStatisticsProject(){}
    void Dataset(int N,int n, string str);//Generate dataset through random numbers. When you want N change and generate new dataset, just call this function!

    void Histogram(int s=10);//get frequancy table
    void Statistic();//calculate average, standard deviation for average
    void ChangeParameter(int n,int s,string str){m_n=n;m_s=s;m_str=str;}
    void PautaFilter();//pauta criterion
};

#endif // SIMPLESTATISTICSPROJECT_H_INCLUDED

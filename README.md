## Course Introduction

### 中文简介
本课程为物理学专业课之一.其主要内容包括:实验数据处理、数值计算和模拟方法等三部分.通过本课程学习,学生能熟练掌握有关计算物理必备的基本方法,为毕业后涉及有关计算的工作或将来读研究生打下良好的基础.

### Introduction in English
This is one of the special courses for the students in physics department. The main contents in this course include three parts: data process, numerical calculation, and simulation methods. By training in this course, the students can master the fundamental methods of computational physics for their future works or studies. 

## 教学目标Overview of the Course

### 学习目标
通过本课程的学习,要求学生能熟练掌握计算物理中所需的数据处理方法、数值计算方法和某些模拟计算方法.为毕业后读研究生或工作中面临有关数据处理或数值计算问题打下良好基础

### 可测量结果
1. 能掌握实验数据处理的基本方法,包括:直方图做法、误差分析和表示、数据拟合、数据平滑处理、数据插值等方法；
2. 掌握基本的数值计算方法.包括:线性代数方程组解法、积分计算法、常微分方程及偏微分方程解法,快速付里叶变换算法等；
3. 掌握Monte Carlo和元胞自动机模拟计算方法等.

## 课程要求

### 授课方式与要求
授课方式:a.多煤体教学.即教师利用多煤体课件进行讲授,但同时利用板书进行补充讲解；b.课后布置作业. 每章书布置1道大型编程并上机操作作业；c..期末闭卷考试 .  
课程要求:学生课堂上认真听讲,并做好必要的笔记,课后按时完成有关作业.通过本课程的学习,学生能利用所学算法解决实际物理及相关计算问题.

### 考试评分与建议
    期末闭卷考试占60％,平时作业及课堂表现占40％.

## 教学安排Syllabus

### 第一章 绪论 (2学时)Introduction
    1.1 计算物理的地位和作用
    1.2 学习计算物理所需要知识
    1.3 编程计算的规范性要求
    1.4 涉及计算物理的科研事例介绍

### 第二章 简单物理实验的模拟(2学时)'Simulation' on Simple Physical Experiments
    2.1 简谐振动实验模拟 Simple harmonic vibration
    2.2 振动合成模拟 The composition of vibration
    2.3 驻波模拟 Standing wave
    2.4 alpha粒子散射计算模拟 Alpha particle scattering

### 第三章 实验数据的统计处理(2学时)Simple Statistic Analysis
    3.1 统计直方图做法 Histogram
    3.2 平均值,方差,标准偏差的算法 Average, Square of error, Standard Diviation
    3.3 误差分析、表示法,错误值剔除法 Source of error, Outlier detection(Three sigma threshold, Chauvenet's criterion)

### 第四章 实验数值的插值 (2学时)Interpolation
    4.1 线性插值法 Linear interpolation
    4.2 二次插值法 Second order Polynomial Interpolation
    4.3 逐次线性插值法
    4.4 n 次插值法 N order Polynomial Interpolation
    4.5 二元函数的多点插值法 Two variable Interpolation

### 第五章 实验数据的拟合(2学时)Data Fitting
    5.1 最小二乘法原理与一元线性拟合 Least squares, Fitting lines
    5.2 多元线性拟合法 Fitting polynomial functions to data
    5.3 非线性曲线拟合法 Fitting non-linear function to data

### 第六章 线性代数方程组解法(2学时)Linear equation set
    6.1 线性代数方程组的直接解法 Analytic Solution Method(Gaussian Elimination)
    6.2 线性代数方程组的迭代解法 Seidel iterative method
    6.3 线性代数方程组数值法的可解条件及注意问题

### 第七章 实验数据的平滑处理 (2学时)Smooting
    7.1 实验数据平滑处理的移动平均法
    7.2 线性加权移动平滑法 unweighted sliding-average method
    7.3 二次加权移动平滑处理法
    7.4 三次加权移动平滑处理法 weighted cubic sliding-average method

### 第八章 静电场与积分计算(2学时)Numerical Integration
    8.1 矩形、梯形和抛物线型积分近似法 Trapezoidal rule
    8.2 变步长辛卜生积分方法 Adaptive Simpson method

### 第九章 RLC电路与常微分方程解法(2学时)Ordinary Differential Equations
    9.1 RC电路与一阶常微分方程解法
    9.2 RLC电路与二阶常微分方程解法
    9.3 龙格-库塔方法

### 第十章 热传导方程的差分方法(2学时)Partial Differential Equations
    10.1 热传导方程介绍
    10.2 一维热传导方程的差分解法
    10.3 二维热传导方程的差分解法

### 第十一章 波动方程和薛定谔方程的数值解法(2学时)Schrodinger Equation 
    11.1 波动方程简介
    11.2 一维波动方程的差分解法
    11.3 薛定谔方程与氢原子能级确定的数值解法

### 第十二章 快速傅立叶变换(2学时)Fast Fourier Transform
    12.1 离散型傅立叶变换及其快速算法
    12.2 快速傅立叶变换算法流程图及编程计算

### 第十三章 Monte Carlo模拟方法I-简单抽样(2学时)Monte Carlo Simulation 1
    13.1 Monte Carlo 模拟简介
    13.2 赝随机数的产生
    13.3 随机数的检验
    13.4 利用随机数进行抽样
    13.5 简单抽样法及其应用

### 第十四章 Monte Carlo模拟方法II-重要抽样(2学时)Monte Carlo Simulation 2
    14.1 重要抽样思想介绍 Importance sampling
    14.2 Metropolis 重要抽样法
    14.3 Ising 模型的Monte Carlo 模拟 MCMC and Ising model

### 第十五章 元胞自动机模拟(2学时)Cellular Automata
    15.1 元胞自动机模拟简介
    15.2 生命游戏机
    15.3 一维元胞自动机规则
    15.4 道路交通元胞自动机模型

## 五、参考教材及相关资料(Reference Books)
陈锺贤,计算物理学,哈尔滨工业大学出版社 Zhongxian Chen, Computational Physics, 2001, HIT press
马文淦,计算物理学,科学出版社 Wengan Ma, Computational Physics, Science press( China )

# What I have learnt in the computational physics course

## A research in computational physics contains three steps: 
1. Construct Model
2. Implement in c++ or other programming language. Use sampling method like Monte Carlo simulation, or use numeric approaches.
3. Data analysis. Find pattern.

## Good coding style -- Comments
1. What can this program do
2. Compiler, how to compile
3. Author, update time
4. Parameter: what's the meaning. The range of them.
5. Interprete what this coding block do. Comments for important statement.

## How to analysis data?
1. Data comes from experiments or computation.
2. From histogram to distribution.
3. Expected value(is the truth-value), variance, 
4. Interpolation
2. Use graph and table. Clear to see(font size...). Provide enough comments in the caption(paramters used for generating data, important result...).
5. Analysis time series data. Cycle exist(change dt)? correlation

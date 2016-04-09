# 各数据文件简介
文件名                       |来源                  |存储内容
---------------------------  |----------------------|-----------
result_dataset.txt           |[../src/SimpleStatistics/main.cpp]|对于每个N的1000行随机产生的数据
result_freqtable.txt         |[../src/SimpleStatistics/main.cpp]|数据集的频数表
result_stat.txt              |[../src/SimpleStatistics/main.cpp]|数据集的简单统计量
result_filter_dataset.txt    |[../src/SimpleStatistics/main.cpp]|采用拉依达法剔除错误值后的数据
result_filter_freqtable.txt  |[../src/SimpleStatistics/main.cpp]|针对剔除后数据的频数分布表
result_filter_stat.txt       |[../src/SimpleStatistics/main.cpp]|针对剔除后数据的简单统计量
README.md                    |                                  |Markdown 语法高亮的帮助文档
datalist.txt                 |awk程序语言提取result_stat.txt信息 |每个N对应的平均值的标准偏差

# 批量数据的有效信息提取
```{bash}
awk -F "\t" 'BEGIN{i=0;OFS="\t";}
{
	if($1~/\#N/){
		match($1,/[0-9]+/,m);
		i=m[0];
	}
	else if($1~/average\ standard\ deviation/){
		print i,$2;
	}
}' result_stat.txt>datalist.txt


```

```
awk -F"\t" '{
sum=0;
for(i=1;i<=NF;i++){
	sum+=$i;
}
sum/=NF;
print sum;
}' result_0.35.txt >result_0.35_average.txt

awk -F"\t" '{
sum=0;
for(i=1;i<=NF;i++){
	sum+=$i;
}
sum/=NF;
print sum;
}' result_0.55_3.txt >result_0.55_3_average.txt
```

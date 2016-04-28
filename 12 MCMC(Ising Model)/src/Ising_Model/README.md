```
mkdir result_drop_3
ls result_0.550000_*|xargs paste -d "\t" >result_0.55_3.txt
mv result_0.550000_* result_drop_3/
ls result_0.350000_*|xargs paste -d "\t" >result_0.35_2.txt
```

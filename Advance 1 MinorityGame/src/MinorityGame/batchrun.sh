#!/bin/bash
i=57
while read line
do
echo $line
echo $line|./program.out
str="SucceedRatio_"$i
paste -d '\t' result_SucceedRatio*>$str".txt"
str="ZeroRatio_"$i
paste -d '\t' result_ZeroRatio*>$str".txt"
rm result*
i=$[ $i + 1 ]
done <$1

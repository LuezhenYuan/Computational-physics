# 使用GNUplot绘图
## 两简谐振动合成的模拟
reset
#set term pngcairo
set terminal pngcairo size 1024,768
set output "simulation1.png"

set size 1,1
set origin 0,0
set xrange [0:300]
set yrange [-2:2]
set datafile separator ","
set ylabel "displacement"
set xlabel "t"

set multiplot
# plot the first graph so that it takes a quarter of the screen
set size 0.5,0.5
set origin 0,0.5
plot "../data/result1" index 0 using 4:1 notitle w lp pt 0
replot "../data/result1" index 0 using 4:2 notitle w lp pt 0
replot "../data/result1" index 0 using 4:3 notitle w lp pt 0


set size 0.5,0.5
set origin 0.5,0.5
plot "../data/result1" index 1 using 4:1 notitle w lp pt 0
replot "../data/result1" index 1 using 4:2 notitle w lp pt 0
replot "../data/result1" index 1 using 4:3 notitle w lp pt 0



set size 0.5,0.5
set origin 0,0
plot "../data/result1" index 2 using 4:1 notitle w lp pt 0
replot "../data/result1" index 2 using 4:2 notitle w lp pt 0
replot "../data/result1" index 2 using 4:3 notitle w lp pt 0



set size 0.5,0.5
set origin 0.5,0
plot "../data/result1" index 3 using 4:1 notitle w lp pt 0
replot "../data/result1" index 3 using 4:2 notitle w lp pt 0
replot "../data/result1" index 3 using 4:3 notitle w lp pt 0


unset multiplot
reset

## 光的多缝衍射

reset
#set term pngcairo
set terminal pngcairo enh size 1024,768
set output "simulation2.png"

set size 1,1
set origin 0,0
set datafile separator ","
set ylabel "I"
set xlabel '{\Symbol q}'

set multiplot
# plot the first graph so that it takes a quarter of the screen
set size 0.5,0.5
set origin 0,0.5
plot "../data/result2" index 0 using 1:2 smooth unique notitle w lp pt 0


set size 0.5,0.5
set origin 0.5,0.5
plot "../data/result2" index 1 using 1:2 smooth unique notitle w lp pt 0



set size 0.5,0.5
set origin 0,0
plot "../data/result2" index 2 using 1:2 smooth unique notitle w lp pt 0



set size 0.5,0.5
set origin 0.5,0
set xrange [-0.02:0.02]
set yrange [0:3]
plot "../data/result2" index 2 using 1:2 smooth unique notitle w lp pt 0

unset multiplot
reset

## alpha粒子散射实验

reset
set datafile separator ","
plot "../src/SimpleSimulation/result3" index 0 using 1:2 notitle w lp pt 0

reset
#set term pngcairo
set terminal pngcairo enh size 1024,768
set output "simulation3.png"

set size 1,1
set origin 0,0
set datafile separator ","
set ylabel "y"
set xlabel 'x'

set multiplot
# plot the first graph so that it takes a quarter of the screen
set size 0.5,1
set origin 0,0
plot "../data/result3" index 0 using 1:2 notitle w lp pt 0, "../data/result3" index 1 using 1:2 notitle w lp pt 0, "../data/result3" index 2 using 1:2 notitle w lp pt 0

set size 0.5,1
set origin 0.5,0
plot "../data/result3" index 0 using 1:2 notitle w lp pt 0, "../data/result3" index 3 using 1:2 notitle w lp pt 0

unset multiplot
reset

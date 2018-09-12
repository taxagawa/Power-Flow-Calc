#!/usr/bin/gnuplot

set terminal png

set title 'Angle' font ",15"
set xr[-1.2:0.1]
set yr[-1.2:0.1]
set xlabel 'output' font ",13"
set ylabel 'ideal solution' font ",13"

set output 'Angle.png'

f(x)=a*x+b
a=1
b=1
fit f(x) "./gnuplot/outputTh.dat" using ANG1:ANG2 via a, b

set label 1 sprintf("{gradient: %.4f}", a) left at graph 0.03,0.9
plot f(x) notitle, "./gnuplot/outputTh.dat" using ANG1:ANG2 notitle with points pt 7 lc 3

replot

#!/usr/bin/gnuplot

set terminal png

set title 'Amplitude' font ",15"
set xr[0.95:1.06]
set yr[0.95:1.06]
set xlabel 'output' font ",13"
set ylabel 'exact solution' font ",13"

set output 'Amplitude.png'

f(x)=a*x+b
a=1
b=1
fit f(x) "./gnuplot/outputAm.dat" using AMP1:AMP2 via a, b

set label 1 sprintf("{gradient: %.4f}", a) left at graph 0.03,0.9
plot f(x) notitle, "./gnuplot/outputAm.dat" using AMP1:AMP2 notitle with points pt 7 lc 3

replot

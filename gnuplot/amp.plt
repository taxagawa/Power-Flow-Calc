set title 'Amplitude' font ",15"
set xr[0.95:1.06]
set yr[0.95:1.06]
set xlabel '結果' font ",13"
set ylabel '厳密解' font ",13"

f(x)=a*x+b
a=1
b=1
fit f(x) "outputAm.dat" using 40:41 via a, b

plot f(x) notitle, "outputAm.dat" using 40:41 notitle with points pt 7 lc 3
set label 1 sprintf("{傾き: %.4f}", a) left at graph 0.03,0.9

replot

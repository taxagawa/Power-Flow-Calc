set xr[0.95:1.06]
set yr[0.95:1.06]

f(x)=a*x+b
a=1
b=1
fit f(x) "outputAm.dat" using 40:41 via a, b

plot f(x), "outputAm.dat" using 40:41 with points pt 7 lc 3

replot

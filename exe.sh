#!/bin/bash

make clean
make
./power

AMP_COLUMN_NUM=$(awk 'END {print NF}' ./gnuplot/outputAm.dat)
AMP_NUM=$(( $(awk 'END {print NF}' ./gnuplot/outputAm.dat) - 1 ))

ANG_COLUMN_NUM=$(awk 'END {print NF}' ./gnuplot/outputTh.dat)
ANG_NUM=$(( $(awk 'END {print NF}' ./gnuplot/outputTh.dat) - 1 ))

#echo $AMP_COLUMN_NUM
#echo $AMP_NUM

# 振幅のプロット
gnuplot -e "
AMP1=${AMP_NUM};
AMP2=${AMP_COLUMN_NUM}" ./gnuplot/amp.gp

# 位相のプロット
gnuplot -e "
ANG1=${ANG_NUM};
ANG2=${ANG_COLUMN_NUM}" ./gnuplot/theta.gp

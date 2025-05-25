set terminal pngcairo size 1000,600
set output "plot.png"

set title "graf"
set xlabel "x"
set ylabel "y"
set grid

plot \
    "data_all.dat" using 1:2 with lines title "graf" lc rgb "black", \
    "data_min.dat" using 1:2 with points pointtype 7 pointsize 1.5 lc rgb "red" title "Мmin", \
    "data_max.dat" using 1:2 with points pointtype 7 pointsize 1.5 lc rgb "blue" title "max"

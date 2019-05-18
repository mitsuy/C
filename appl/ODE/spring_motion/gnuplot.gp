set term postscript eps
set output 'x.eps'

set xlabel "time"
set ylabel "x"

plot "result_eem.dat" u 1:2 ps 2 w p,\
     "result_rk4.dat" u 1:2 ps 2 w p
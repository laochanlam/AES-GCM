reset
set ylabel 'time(sec)/10000 time'
set xlabel 'random_number'
set style fill solid
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'
unset xtics


plot [:][:]'Instrinics.txt' using :2 title 'random number'

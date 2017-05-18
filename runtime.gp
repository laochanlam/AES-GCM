reset
set ylabel 'time(sec)'
set xlabel 'value'
set style fill solid
set title 'perfomance comparison'
set term png enhanced font 'Verdana,10'
set output 'runtime.png'


plot [:][:]'Instrinics.txt' using 1:2 title 'Value'

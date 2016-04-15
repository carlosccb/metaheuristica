#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "graficoKPTiempo.eps"
set key right bottom
set xlabel "Número de ejecucion"
set ylabel "Tiempo mejor Solucion"

plot 'KP_Fitness&Time.txt' using 1:4 t "Tiempo" w l

set output "graficoTSPTiempo.eps"
plot 'TSP_Fitness&Time.txt' using 1:4 t "Tiempo" w l
_end_

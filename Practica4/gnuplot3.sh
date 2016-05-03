#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "graficoKPiteraciones.eps"
set key right bottom
set xlabel "Numero de ejecucion"
set ylabel "Númeor de iteraciones"

plot 'KP_Fitness&Time.txt' using 1:5 t "Iteraciones" w l

set output "graficoTSPiteraciones.eps"
plot 'TSP_Fitness&Time.txt' using 1:5 t "Iteraciones" w l
_end_

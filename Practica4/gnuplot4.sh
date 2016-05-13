#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "graficoKPGenetico.eps"
set key right bottom
set xlabel "Numero de Iteracion"
set ylabel "Fitness"

plot 'KP_Iteraciones.txt' using 1:2 t "Mejora del fitness" w l

set output "graficoTSPGenetico.eps"
plot 'TSP_Iteraciones.txt' using 1:2 t "Mejora del fitness" w l
_end_

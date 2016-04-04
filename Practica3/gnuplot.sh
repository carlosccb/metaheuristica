#!/bin/bash

cat << _end_ | gnuplot
set terminal postscript eps color
set output "graficoKPfitness.eps"
set key right bottom
set xlabel "Numero de iteracion"
set ylabel "Fitness Solucion"

plot 'KP_Fitness&Time.txt' using 1:2 t "Fitness inicial" w l, 'KP_Fitness&Time.txt' using 1:3 t "Fitness final" w l

set output "graficoTSP.eps"
plot 'TSP_Fitness&Time.txt' using 1:2 t "Fitness inicial" w l, 'TSP_Fitness&Time.txt' using 1:3 t "Fitness final" w l
_end_

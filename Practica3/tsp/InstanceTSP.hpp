#ifndef __INSTANCE_TSP_HPP__
#define __INSTANCE_TSP_HPP__

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include <vector>

#include "../lib/Instance.hpp"
#include "../lib/Miscelanea.hpp"
#include "SolucionViajante.hpp"

class InstanceTSP : public Instance {
	public:
		InstanceTSP() {}
		//Valores del constructor adaptados a los archivos csv de esta practica
		InstanceTSP(std::string file_name, int header_lines=6, int length_line=3, char separator=' ', int end_lines = 0)
			: Instance(file_name, header_lines, length_line, separator, end_lines)
		{}

		~InstanceTSP() 
		{
			if(_file.is_open())
				_file.close();
		}

		double distancia(const problem_element a, const problem_element b) {
			return sqrt(pow(a.a - b.a,2) + pow(a.b - b.b,2));
		}


		double getAptitude(vector <problem_element> &info, const SolucionViajante &solution){

			double sumatorio = 0.0;

			for(unsigned int i = 0; i < (info.size() - 1); i++){

				//Sumamos la distancia entre el origen y el destino de cada camino de la solucion
				sumatorio += distancia(info[ solution.getSolucion(i) ], info[ solution.getSolucion(i+1) ]);

			}

			return sumatorio;
		}



		//Funcion que almacena en un fichero una serie de datos de salida del programa
	      void saveResults(const SolucionViajante &inicial, const double &best_fitness, const SolucionViajante &best_solution, double tiempo, int iteraciones = 0){


		  int id = 1;	//Identificador del numero de ejecucion del programa
		  string line;

		  ifstream fr("TSP_Fitness&Time.txt");
			
			//Contamos cual ejecucion del programa es esta
			if(fr.is_open()){
				while(! fr.eof()){

					getline(fr, line);
					id++;
				}
			}

			fr.close();


		  ofstream fs("TSP_soluciones.txt", std::ofstream::app);	//Abrimos el flujo de salida al fichero


			//Escribimos los resultados de esta ejecucion
			fs << "Ejecución " << id << ":" << endl;
                        for (int i = 0; i < inicial.getSolucion().size(); i++){
                             fs << inicial.getSolucion(i);
                              if (i != inicial.getSolucion().size() -1) fs << "-> ";
                          }
                        fs << endl << endl;
                        for (int i = 0; i < best_solution.getSolucion().size(); i++){
                             fs << best_solution.getSolucion(i);
                               if (i != best_solution.getSolucion().size() -1) fs << "-> ";
                          }
                          



                        fs << endl << "Fitness inicial: " << inicial.getFitness() << " Fitness mejora: " << best_fitness  << "\t" << "Tiempo de ejecución: " << tiempo << "\n" << "\n" << "\n" << "\n";

			fs.close();


		  fs.open("TSP_Fitness&Time.txt", std::ofstream::app);
                  if (id != 1) fs << endl;
                  fs << id << " " << inicial.getFitness() << " " << best_fitness << " " << tiempo << " " << iteraciones;
                  fs.close();
                  


		}

};

#endif

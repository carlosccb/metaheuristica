#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>


#include "lib/Interfaz.hpp"

#include "lib/Instance.hpp"
#include "kp/InstanceKP.hpp"
#include "tsp/InstanceTSP.hpp"
#include "kp/SolucionMochila.hpp"
#include "tsp/SolucionViajante.hpp"
#include "kp/SolGeneratorMochila.hpp"
#include "tsp/SolGeneratorViajante.hpp"


using namespace std;

int main(int argc, char **argv) {
	Interfaz cli;
	int i;
	int veces;
	srand(time(NULL));


	//Siempre se ejcuta hasta que el usuario quiera salir
	while(true) {
		if(not cli.option_menu())
			break;

		//Se ejecuta hasta que se carga una instancia de un fichero valido
		vector<problem_element> inst_v = cli.read_instance(veces);

		//El problema seleccionado es TSP
		if(cli.getOpt() == 1){
			InstanceTSP tsp_instance;
			SolucionViajante best_solution(inst_v.size()), current_solution;
			SolGeneratorViajante sol_gen;
			double best_fitness, actual_fitness;
			
			for (i = 0; i < veces; i++){
				//Obtenemos 1000 soluciones diferentes, usamos la primera para inicializar best_fitness, sera el punto de partida
				current_solution = sol_gen.randomSolutionGenerator(inst_v.size());
				best_fitness = tsp_instance.getAptitude(inst_v, current_solution);
	
				for(unsigned int i = 0; i < 1000; i++){
					current_solution = sol_gen.randomSolutionGenerator(inst_v.size());
					actual_fitness = tsp_instance.getAptitude(inst_v, current_solution);

					if(actual_fitness < best_fitness){
						best_solution = current_solution;
						best_fitness = actual_fitness;
					}
			}
				//Muestra la solucion
				cout << "Para la ejecución: " << i+1 << endl << "El orden del recorrido es :\n";
				for(auto i : best_solution.getSolucion())
					cout << i << " -> ";

				cout << "\ny la distancia total recorrida " << best_fitness << endl;

				tsp_instance.saveResults(best_fitness, best_solution);		//Guardamos el resultado
			}
		//El problema seleccionado es KP
		} else{
			InstanceKP kp_instance;
			SolucionMochila best_solution(inst_v.size()), current_solution;
			SolGeneratorMochila sol_gen;
			double best_fitness, actual_fitness;
			double KP_size = cli.getCapacity();	//Capacidad de la mochila

			cout << "\nLa capacidad de la mochila es: " << cli.getCapacity() << endl;
			for (i = 0; i < veces; i++){
				//Obtenemos 1000 soluciones diferentes, usamos la primera para inicializar best_fitness, sera el punto de partida
				current_solution = sol_gen.randomSolutionGenerator(inst_v.size());
				best_fitness = kp_instance.getAptitude(current_solution, KP_size, inst_v);

				for(unsigned int i = 0; i < 1000; i++){
					current_solution = sol_gen.randomSolutionGenerator(inst_v.size());
					actual_fitness = kp_instance.getAptitude(current_solution, KP_size, inst_v);

					if(actual_fitness > best_fitness){
						best_solution = current_solution;
						best_fitness = actual_fitness;
					}
			}
                        	cout << "El mejor fitness es: " << best_fitness <<  " para la ejecución: " << i+1 << endl;
				kp_instance.saveResults(best_fitness, best_solution);	//Guardamos el resultado
			}
		}

	}

	return 0;
}


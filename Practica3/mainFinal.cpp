#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>


#include "lib/Interfaz.hpp"

#include "lib/Instance.hpp"
#include "kp/InstanceKP.hpp"
#include "tsp/InstanceTSP.hpp"
#include "kp/SolucionMochila.hpp"
#include "tsp/SolucionViajante.hpp"
#include "kp/SolGeneratorMochila.hpp"
#include "tsp/SolGeneratorViajante.hpp"

#include "kp/localSearchKP.hpp"
#include "tsp/localSearchTSP.hpp"
#include "kp/neighborExploratorKP.hpp"
#include "tsp/neighborExploratorTSP.hpp"
#include "kp/neighborOperatorKP.hpp"
#include "tsp/neighborOperatorTSP.hpp"
#include "kp/coolingExploratorKP.hpp"
#include "tsp/coolingExploratorTSP.hpp"
#include "kp/GRASPExploratorKP.hpp"
#include "tsp/GRASPExploratorTSP.hpp"




using namespace std;

int main(int argc, char **argv) {


	Interfaz cli;
	int i;
	int veces;
	srand(time(NULL));
	double tiempo, tiempoTotal = 0.0;
	int iteraciones;


	//Siempre se ejcuta hasta que el usuario quiera salir
	while(true) {

		if(not cli.option_menu())
			break;


		//Se ejecuta hasta que se carga una instancia de un fichero valido
		vector<problem_element> info = cli.read_instance(veces);


		//El problema seleccionado es TSP
		if(cli.getOpt() == 1){


			neighborOperatorTSP operadorVecindario(info);
			InstanceTSP instance;


			//Escogemos Enfriamiento Simulado
			if(cli.getOptExplo() == 1){

                                tiempoTotal=0.0;

				SolGeneratorViajante randomSolution;
				coolingExploratorTSP notFrozen(operadorVecindario);
				SolucionViajante finalSolution, initialSolution;
                                clock_t time; 

				for(int i = 0; i < 50; i++){
                                time = clock();

					cout << "Iteracion: " << i << endl;

					initialSolution = randomSolution.randomSolutionGenerator(info.size());
					initialSolution.setAptitude(info);

					finalSolution = notFrozen.enfriamientoSimuladoTSP(info, initialSolution);
                                 tiempo = ((double) (clock() - time)/CLOCKS_PER_SEC);
                                 tiempoTotal = tiempoTotal + tiempo;
                                 instance.saveResults(initialSolution, finalSolution.getFitness(), finalSolution, tiempo);
                                 cout << "Tiempo de ejecucion: " << tiempo << " Total: "<< tiempoTotal << endl;

				}

			}


			//Escogemos GRASP
			else{

                                tiempoTotal=0.0;


				SolucionViajante finalSolution;

				firstImprovementTSP exploradorVecindario(operadorVecindario);
				localSearchTSP busquedaLocal(operadorVecindario, exploradorVecindario);
                                clock_t time;

				GRASPExploratorTSP GRASPing_berries(busquedaLocal);


				for(int i = 0; i < 50; i++){
                                time = clock();


					cout << "Iteracion: " << i << endl;
					finalSolution = GRASPing_berries.GRASP(info);
                                 tiempo = ((double) (clock() - time)/CLOCKS_PER_SEC);
                                 tiempoTotal = tiempoTotal + tiempo;
                                 instance.saveResults(finalSolution, finalSolution.getFitness(), finalSolution, tiempo);
                                 cout << "Tiempo de ejecucion: " << tiempo << " Total: "<< tiempoTotal << endl;

				}

			}




		}



		/*####################################################################################*/
		/*####################################################################################*/



		//El problema seleccionado es KP
		else{



			neighborOperatorKP operadorVecindario(cli.getCapacity(), info);
			InstanceKP instance;


			//Usamos el metodo de Enfriamiento Simulado
			if(cli.getOptExplo() == 1){

                                tiempoTotal=0.0;

				SolGeneratorMochila randomSolution;
				coolingExploratorKP notFrozen(operadorVecindario);
				SolucionMochila finalSolution, initialSolution;
                                clock_t time;

				for(int i = 0; i < 50; i++){
                                time = clock();


					cout << "Iteracion: " << i << endl;

					initialSolution = randomSolution.randomSolutionGenerator(info.size());
					initialSolution.setAptitude(cli.getCapacity(), info);

					finalSolution = notFrozen.enfriamientoSimuladoKP(info, initialSolution);
                                 tiempo = ((double) (clock() - time)/CLOCKS_PER_SEC);
                                 tiempoTotal = tiempoTotal + tiempo;
                                 instance.saveResults(initialSolution, finalSolution.getFitness(), finalSolution, tiempo);
                                 cout << "Tiempo de ejecucion: " << tiempo << " Total: "<< tiempoTotal << endl;

				}

			}


			//Usamos el GRASP
			else{

                                tiempoTotal=0.0;

				SolucionMochila finalSolution;

				firstImprovementKP exploradorVecindario(operadorVecindario);
				localSearchKP busquedaLocal(operadorVecindario, exploradorVecindario);
                                clock_t time;

				GRASPExploratorKP GRASPing_berries(busquedaLocal);


				for(int i = 0; i < 50; i++){
                                 
                                time = clock();

					cout << "Iteracion: " << i << endl;
					finalSolution = GRASPing_berries.GRASP(info);
					cout << "Fitness Iteracion = " << finalSolution.getFitness() << endl;
                                 tiempo = ((double) (clock() - time)/CLOCKS_PER_SEC);
                                 tiempoTotal = tiempoTotal + tiempo;
                                 instance.saveResults(finalSolution, finalSolution.getFitness(), finalSolution, tiempo);
                                 cout << "Tiempo de ejecucion: " << tiempo << " Total: "<< tiempoTotal << endl;

				}

			}


		}

	}	//Fin while(true)

	return 0;
}


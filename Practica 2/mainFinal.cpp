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
		vector<problem_element> info = cli.read_instance(veces);

               for (i = 0; i < veces; i++){

		//El problema seleccionado es TSP
		if(cli.getOpt() == 1){

			neighborOperatorTSP operadorVecindario(info);
			SolGeneratorViajante randomSolution;
                        InstanceTSP instance;

			//Generamos la solucion aleatoria inicial
			SolucionViajante initialSolution;
			initialSolution = randomSolution.randomSolutionGenerator(info.size());


			//Escogemos la primera mejora
			if(cli.getOptExplo() == 1){


				double localOptimumFitness;
				SolucionViajante localOptimumSolution;
                                clock_t time = clock(); 

				firstImprovementTSP exploradorVecindario(operadorVecindario);
				localSearchTSP busquedaLocal(operadorVecindario, exploradorVecindario);

				//Ejecutamos la busqueda local
				busquedaLocal.localOptimum(initialSolution, localOptimumSolution, localOptimumFitness);
                      instance.saveResults(localOptimumFitness, localOptimumSolution);
                         cout << "Tiempo de ejecucion: " << ((double) (clock() - time)/CLOCKS_PER_SEC) << endl;
			}


			//Escogemos la mejor mejora
			else{

				double localOptimumFitness;
				SolucionViajante localOptimumSolution;
                                clock_t time = clock();

				bestImprovementTSP exploradorVecindario(operadorVecindario);
				localSearchTSP busquedaLocal(operadorVecindario, exploradorVecindario);

				//Ejecutamos la busqueda local
				busquedaLocal.localOptimum(initialSolution, localOptimumSolution, localOptimumFitness);
                      instance.saveResults(localOptimumFitness, localOptimumSolution);
                         cout << "Tiempo de ejecucion: " << ((double) (clock() - time)/CLOCKS_PER_SEC) << endl;

			}




		}
		/*####################################################################################*/
		/*####################################################################################*/



		//El problema seleccionado es KP
		else{


			neighborOperatorKP operadorVecindario(info.size(), info);
			SolGeneratorMochila randomSolution;
                        InstanceKP instance;

			//Generamos la solucion aleatoria inicial
			SolucionMochila initialSolution;
			initialSolution = randomSolution.randomSolutionGenerator(info.size());


			if(cli.getOptExplo() == 1){


				double localOptimumFitness;
				SolucionMochila localOptimumSolution;
                                clock_t time = clock();

				firstImprovementKP exploradorVecindario(operadorVecindario);
				localSearchKP busquedaLocal(operadorVecindario, exploradorVecindario);

				//Ejecutamos la busqueda local
				busquedaLocal.localOptimum(initialSolution, localOptimumSolution, localOptimumFitness);
                      instance.saveResults(localOptimumFitness, localOptimumSolution);
                         cout << "Tiempo de ejecucion: " << ((double) (clock() - time)/CLOCKS_PER_SEC) << endl;
			}



			else{

				double localOptimumFitness2;
				SolucionMochila localOptimumSolution2;
                                clock_t time = clock();

				bestImprovementKP exploradorVecindario(operadorVecindario);
				localSearchKP busquedaLocal(operadorVecindario, exploradorVecindario);

				//Ejecutamos la busqueda local
				busquedaLocal.localOptimum(initialSolution, localOptimumSolution2, localOptimumFitness2);
                      instance.saveResults(localOptimumFitness2, localOptimumSolution2);
                         cout << "Tiempo de ejecucion: " << ((double) (clock() - time)/CLOCKS_PER_SEC) << endl;

			}


		}


               }

	}	//Fin while(true)

	return 0;
}


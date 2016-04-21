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
	double tiempo;
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

				SolGeneratorViajante randomSolution;
				coolingExploratorTSP notFrozen(operadorVecindario);
				SolucionViajante finalSolution, initialSolution;

				for(int i = 0; i < 50; i++){


					initialSolution = randomSolutionrandom.SolutionGenerator(info.size());
					initialSolution.setAptitude(info);

					finalSolution = notFrozen.enfriamientoSimuladoTSP(info, initialSolution);

					cout << "Iteracion: " << i << endl;

				}

			}


			//Escogemos GRASP
			else{


				SolucionViajante finalSolution;

				firstImprovementTSP exploradorVecindario(operadorVecindario);
				localSearchTSP busquedaLocal(operadorVecindario, exploradorVecindario);

				GRASPExploratorTSP GRASPing_berries(busquedaLocal);


				for(int i = 0; i < 50; i++){


					finalSolution = GRASPing_berries.GRASP(info);


					cout << "Iteracion: " << i << endl;

				}

			}




		}



		/*####################################################################################*/
		/*####################################################################################*/



		//El problema seleccionado es KP
		else{



			neighborOperatorKP operadorVecindario(info);
			InstanceKP instance;


			//Usamos el metodo de Enfriamiento Simulado
			if(cli.getOptExplo() == 1){

				SolGeneratorMochila randomSolution;
				coolingExploratorKP notFrozen(operadorVecindario);
				SolucionMochila finalSolution, initialSolution;

				for(int i = 0; i < 50; i++){


					initialSolution = randomSolution.randomSolutionGenerator(info.size());
					initialSolution.setAptitude(info);

					finalSolution = notFrozen.enfriamientoSimuladoKP(info, initialSolution);

					cout << "Iteracion: " << i << endl;

				}

			}


			//Usamos el GRASP
			else{



				SolucionMochila finalSolution;

				firstImprovementKP exploradorVecindario(operadorVecindario);
				localSearchKP busquedaLocal(operadorVecindario, exploradorVecindario);

				GRASPExploratorKP GRASPing_berries(busquedaLocal);


				for(int i = 0; i < 50; i++){


					finalSolution = GRASPing_berries.GRASP(info);


					cout << "Iteracion: " << i << endl;

				}

			}


		}

	}	//Fin while(true)

	return 0;
}


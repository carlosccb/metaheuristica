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
#include "tsp/geneticAlgorithmTSP.hpp"




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


			InstanceTSP instance;
			geneticAlgorithmTSP aReproducirse(info);

			SolucionViajante solucionFinal = aReproducirse.GA();

//			cout << endl << "Fitness: " << solucionFinal.getFitness() << endl << endl;

		}



		/*####################################################################################*/
		/*####################################################################################*/



		//El problema seleccionado es KP
		else{





		}

	}	//Fin while(true)

	return 0;
}


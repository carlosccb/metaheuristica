#ifndef		__LOCAL_SEARCH_KP__
#define		__LOCAL_SEARCH_KP__


#include <vector>

#include "../lib/Miscelanea.hpp"

#include "neighborOperatorKP.hpp"
#include "neighborExploratorKP.hpp"
#include "SolucionViajante.hpp"



using namespace std;


class localSearchKP{


	private:

		double _bestFitness = 0;
		SolucionMochila _bestSolution;

		neighborOperator _operador;

		bestImrpovementKP * _bestExplo = NULL;
		firstImrpovementKP * _firstExplo = NULL;


	public:

		//Constructores
		localSearch(neighborOperatorKP &operador, firstImprovementKP &explorador){

			_operador = operador;
			_firstExplo = &explorador;

		}

		localSearch(neighborOperatorKP &operador, bestImprovementKP &explorador){

			_operador = operador;
			_bestExplo = &explorador;

		}
		

		//Modificadores
		void setFitness(double &bestFitness){_bestFitness = bestFitness;};
		void setSolution(SolucionMochila &bestSolution){_bestSolution = bestSolution;};


		//Observadores
		double getFitness(){return _bestFitness;};
		SolucionMochila getSolution(){return _bestSolution;};
		neighborOperatorKP getOperator(){return _operador;};



		//Metodo que devuelve el optimo local ¿Y su valor de fitness?
		void localOptimum(vector <problem_element> &info, const int &KPSize, const SolucionMochila &initialSolution, SolucionMochila &optimumSolution, double &optimumFitness){


		  int iteraciones = 1000, contador = 0;		//Cuenta el numero de veces que el optimo no varia
		  double actualFitness;
		  SolucionMochila actualSolution;


			_bestSolution = initialSolution;

			while(iteraciones > 0 && contador < 2){


				if(_firstImprovementKP != NULL)

					actualSolution = _firstImprovementKP->explorateNeighborhood(KPSize, info, bestSolution);


				else

					actualSolution = _bestImprovementKP->explorateNeighborhood(KPSize, info, bestSolution);



				actualFitness = actualSolution.getAptitude(info, KPSize);


				/*

					La Solucion devuelta en cada iteracion solo puede ser igual o mejor que
				la antetior, porque se incluye a si misma en el vecindario para compararse

																							*/

				if(bestFitness == actualFitness)

					contador++;


				else{

					_bestFitness = actualFitness;
					_bestSolution = actualSolution;

					contador = 0;
				}


				iteraciones--;
			}



			//Al ser clase, podemos hacer esto fuera de la funcion con los observadores
			optimumSolution = _bestSolution;
			optimumFitness = _bestFitness;
		}


};

#endif

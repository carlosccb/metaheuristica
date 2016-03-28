#ifndef		__LOCAL_SEARCH_TSP__
#define		__LOCAL_SEARCH_TSP__


#include <vector>

#include "../lib/Miscelanea.hpp"

#include "neighborOperatorTSP.hpp"
#include "neighborExploratorTSP.hpp"
#include "SolucionViajante.hpp"



using namespace std;




class localSearchTSP{


	private:

		double _bestFitness = 0;
		SolucionViajante _bestSolution;

		neighborOperator _operador;

		bestImrpovementTSP * _bestExplo = NULL;
		firstImrpovementTSP * _firstExplo = NULL;


	public:

		//Constructores
		localSearch(neighborOperatorTSP &operador, firstImprovementTSP &explorador){

			_operador = operador;
			_firstExplo = &explorador;

		}

		localSearch(neighborOperatorTSP &operador, bestImprovementTSP &explorador){

			_operador = operador;
			_bestExplo = &explorador;

		}
		

		//Modificadores
		void setFitness(double &bestFitness){_bestFitness = bestFitness;};
		void setSolution(SolucionViajante &bestSolution){_bestSolution = bestSolution;};


		//Observadores
		double getFitness(){return _bestFitness;};
		SolucionViajante getSolution(){return _bestSolution;};
		neighborOperatorTSP getOperator(){return _operador;};



		//Metodo que devuelve el optimo local ¿Y su valor de fitness?
		void localOptimum(vector <problem_element> &info, const SolucionViajante &initialSolution, SolucionViajante &optimumSolution, double &optimumFitness){


		  int iteraciones = 1000, contador = 0;		//Cuenta el numero de veces que el optimo no varia
		  double actualFitness;
		  SolucionViajante actualSolution;


			_bestSolution = initialSolution;

			while(iteraciones > 0 && contador < 2){


				if(_firstImprovementTSP != NULL)

					actualSolution = _firstImprovementTSP->explorateNeighborhood(info, _bestSolution);


				else

					actualSolution = _bestImprovementTSP->explorateNeighborhood(info, _bestSolution);
				

				actualFitness = actualSolution.getAptitude(info);


				/*

					La solucion devuelta en cada iteracion solo puede ser igual o mejor que
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

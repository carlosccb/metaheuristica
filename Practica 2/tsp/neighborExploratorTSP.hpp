#ifndef		__NEIGHBOR_EXPLORATOR_TSP__
#define		__NEIGHBOR_EXPLORATOR_TSP__


#include <vector>

#include "../lib/Miscelanea.hpp"

#include "SolucionViajante.hpp"
#include "neighborOperator.hpp"


using namespace std;



class neighborExploratorTSP{


	private:

		neighborOperatorTSP _operador;


	public:

		//Constructores
		neighborExplorator(){};
		neighborExplorator(neighborOperatorTSP &operador){

			_operador = operador;

		}

		//Modificadores
		void setOperator(neighborOperatorTSP &operador){_operador = operador;};

		//Observadores
		neighborOperatorTSP getOperator(){return _operador;};
};






class firstImprovementTSP: public neighborExploratorTSP{



	public:

		//Constructores
		firstImprovementTSP(){};
		firstImprovementTSP(neighborOperatorTSP &operador): neighborExploratorTSP(operador){};


		//Metodo que explora el vecindario en funcion de la estrategia (best o first)
		SolucionViajante explorateNeighborhood(vector <problem_element> &info, const SolucionViajante &initialSolution){


		  double actualFitness, bestFitness;
		  SolucionViajante bestSolution, actualSolution;


			bestSolution = initialSolution;
			bestFitness = bestSolution.getAptitude(info);


			for(int i = 0; i < info.size() - 1; i++){

				for(int j = i + 1; j < info.size(); j++){



					actualSolution = getOperator().generateNeighbor(initialSolution, i, j);
					actualFitness = actualSolution.getAptitude(info);


					if(actualFitness < bestFitness)

						return actualSolution;	//Devolvemos el nuevo optimo
				
				}

			}


			return initialSolution;			//El optimo sigue siendo el mismo
		}


};




class bestImprovementTSP: public neighborExploratorTSP{



	public:

		//Constructores
		bestImprovementTSP(){};
		bestImprovementTSP(neighborOperatorTSP &operador): neighborExploratorTSP(operador){};



		//Metodo que explora el vecindario en funcion de la estrategia (best o first)
		SolucionViajante explorateNeighborhood(vector <problem_element> &info, const SolucionViajante &initialSolution){


		  double actualFitness, bestFitness;
		  SolucionViajante bestSolution, actualSolution;


			bestSolution = initialSolution;
			bestFitness = bestSolution.getAptitude(info);


			for(int i = 0; i < info.size() - 1; i++){

				for(int j = i + 1; j < info.size(); j++){



					actualSolution = getOperator().generateNeighbor(initialSolution, i, j);
					actualFitness = actualSolution.getAptitude(info);


					if(actualFitness < bestFitness){

						bestFitness = actualFitness;
						bestSolution = actualSolution;
					}
				}

			}


			return bestSolution;			//Devolvemos el ¿nuevo? optimo
		}


};




#endif

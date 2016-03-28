#ifndef		__NEIGHBOR_EXPLORATOR_KP__
#define		__NEIGHBOR_EXPLORATOR_KP__


#include <vector>

#include "../lib/Miscelanea.hpp"

#include "neighborOperator.hpp"

using namespace std;


class neighborExploratorKP{


	private:

		neighborOperatorKP _operador;


	public:

		//Constructores
		neighborExplorator(){};
		neighborExplorator(neighborOperatorKP &operador){

			_operador = operador;

		}

		//Modificadores
		void setOperator(neighborOperatorKP &operador){_operador = operador;};

		//Observadores
		neighborOperatorKP getOperator(){return _operador;};

};






class firstImprovementKP: public neighborExploratorKP{



	public:

		//Constructores
		firstImprovementKP(){};
		firstImprovementKP(neighborOperatorKP &operador): neighborExploratorKP(operador){};



		//Metodo que explora el vecindario en funcion de la estrategia (best o first)
		SolucionMochila explorateNeighborhood(const int &KPSize, vector <problem_element> &info, const SolucionViajante &initialSolution){


		  double actualFitness, bestFitness;
		  SolucionMochila bestSolution, actualSolution;


			bestSolution = initialSolution;
			bestFitness = bestSolution.getAptitude(info);


			for(int i = 0; i < info.size(); i++){


				actualSolution = getOperator().generateNeighbor(initialSolution, i);
				actualFitness = actualSolution.getAptitude(info);


				if(actualFitness > bestFitness)

					return actualSolution;	//Devolvemos el nuevo optimo

			}


			return initialSolution;			//El optimo sigue siendo el mismo
};







class bestImprovementKP: public neighborExploratorKP{



	public:

		//Constructores
		bestImprovementKP(){};
		bestImprovementKP(neighborOperatorKP &operador): neighborExploratorKP(operador){};



		//Metodo que explora el vecindario en funcion de la estrategia (best o first)
		SolucionMochila explorateNeighborhood(const int &KPSize, vector <problem_element> &info, const SolucionViajante &initialSolution){

		  double actualFitness, bestFitness;
		  SolucionMochila bestSolution, actualSolution;

			bestSolution = initialSolution;
			bestFitness = bestSolution.getFitness();


			for(int i = 0; i < info.size(); i++){


				actualSolution = getOperator().generateNeighbor(initialSolution, i);
				actualFitness = actualSolution.getFitness();


				if(actualFitness > bestFitness){

					bestFitness = actualFitness;
					bestSolution = actualSolution;
				}

			}


			return bestSolution;			//Devolvemos el ¿nuevo? optimo
		}


};




#endif

#ifndef		__NEIGHBOR_EXPLORATOR_TSP__
#define		__NEIGHBOR_EXPLORATOR_TSP__


#include <vector>

#include "../lib/Miscelanea.hpp"

#include "SolucionViajante.hpp"
#include "neighborOperatorTSP.hpp"


using namespace std;



class neighborExploratorTSP{


	private:

		neighborOperatorTSP _operador;


	public:

		//Constructores
		neighborExploratorTSP(){};
		neighborExploratorTSP(neighborOperatorTSP &operador){

			_operador = operador;

		}


		//Sobrecarga operador igual
		neighborExploratorTSP & operator=(const neighborExploratorTSP &s){

			if(this != &s){

				this->_operador = s.getOperator();
			}

		  return *this;
		};

		//Modificadores
		void setOperator(neighborOperatorTSP &operador){_operador = operador;};

		//Observadores
		neighborOperatorTSP getOperator() const {return _operador;};
};






class firstImprovementTSP: public neighborExploratorTSP{



	public:

		//Constructores
		firstImprovementTSP(){};
		firstImprovementTSP(neighborOperatorTSP &operador): neighborExploratorTSP(operador){};


		//Metodo que explora el vecindario en funcion de la estrategia (best o first)
		SolucionViajante explorateNeighborhood(const SolucionViajante &initialSolution){


		  double actualFitness, bestFitness;
		  SolucionViajante bestSolution, actualSolution;


			bestSolution = initialSolution;
			bestFitness = bestSolution.getFitness();


			for(int i = 0; i < getOperator().getInfo().size() - 1; i++){

				for(int j = i + 1; j < getOperator().getInfo().size(); j++){



					actualSolution = getOperator().generateNeighbor(initialSolution, i, j);
					actualFitness = actualSolution.getFitness();


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
		SolucionViajante explorateNeighborhood(const SolucionViajante &initialSolution){


		  double actualFitness, bestFitness;
		  SolucionViajante bestSolution, actualSolution;


			bestSolution = initialSolution;
			bestFitness = bestSolution.getFitness();


			for(int i = 0; i < getOperator().getInfo().size() - 1; i++){

				for(int j = i + 1; j < getOperator().getInfo().size(); j++){



					actualSolution = getOperator().generateNeighbor(initialSolution, i, j);
					actualFitness = actualSolution.getFitness();


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

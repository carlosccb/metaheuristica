#ifndef		__LOCAL_SEARCH_KP__
#define		__LOCAL_SEARCH_KP__


#include <vector>

#include "../lib/Miscelanea.hpp"

#include "neighborOperatorKP.hpp"
#include "neighborExploratorKP.hpp"
#include "SolucionMochila.hpp"


using namespace std;


class localSearchKP{


	private:

		double _bestFitness = 0;
		SolucionMochila _bestSolution;

		neighborOperatorKP _operador;

		bestImprovementKP _bestExplo;
		firstImprovementKP _firstExplo;
		bool isBestExplorator;


	public:

		//Constructores
		localSearchKP(){};
		localSearchKP(neighborOperatorKP &operador, firstImprovementKP &explorador){

			_operador = operador;
			_firstExplo = explorador;

			isBestExplorator = false;
		}

		localSearchKP(neighborOperatorKP &operador, bestImprovementKP &explorador){

			_operador = operador;
			_bestExplo = explorador;

			isBestExplorator = true;
		}


		//Sobrecarga operador igual
		localSearchKP & operator=(const localSearchKP &s){

			if(this != &s){

				this->_operador = s.getOperator();
				this->_bestSolution = s.getSolution();
				this->_bestExplo = s.getExploratorBest();
				this->_firstExplo = s.getExploratorFirst();

				this->isBestExplorator = s.exploratorType();
			}

		  return *this;
		};



		//Modificadores
		void setSolution(SolucionMochila &bestSolution){_bestSolution = bestSolution;};


		//Observadores
		SolucionMochila getSolution() const {return _bestSolution;};
		neighborOperatorKP getOperator() const {return _operador;};

		bestImprovementKP getExploratorBest() const {return _bestExplo;}
		firstImprovementKP getExploratorFirst() const {return _firstExplo;}
		bool exploratorType() const {return isBestExplorator;}


		//Metodo que devuelve el optimo local ¿Y su valor de fitness?
		int localOptimum(const SolucionMochila &initialSolution, SolucionMochila &optimumSolution, double &optimumFitness){


		  int iteraciones = 1000, contador = 0;		//Cuenta el numero de veces que el optimo no varia
		  double actualFitness;
		  SolucionMochila actualSolution;


			_bestSolution = initialSolution;

			while(contador < 2){


				if(! isBestExplorator)

					actualSolution = _firstExplo.explorateNeighborhood(_bestSolution);


				else

					actualSolution = _bestExplo.explorateNeighborhood(_bestSolution);



				actualFitness = actualSolution.getFitness();


				/*

					La Solucion devuelta en cada iteracion solo puede ser igual o mejor que
				la antetior, porque se incluye a si misma en el vecindario para compararse

																							*/

				if(_bestFitness == actualFitness)

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

                        return 1000-iteraciones; //para saber cuantas iteraciones hemos realizado
		}


};

#endif

#ifndef		__GENETIC_ALGORITHM_TSP__
#define		__GENETIC_ALGORITHM_TSP__


#include <cstdlib>
#include <cmath>
#include <vector>
#include <ctime>

#include "../lib/Miscelanea.hpp"

#include "SolucionViajante.hpp"
#include "SolGeneratorViajante.hpp"
#include "neighborOperatorTSP.hpp"
#include "neighborExploratorTSP.hpp"
#include "localSearchTSP.hpp"

#include <iostream>

#define POP_SIZE 50
#define MAX 128

using namespace std;



class geneticAlgorithmTSP{



	private:

		vector <SolucionViajante> _population;
		vector <problem_element> _info;

	public:


		geneticAlgorithmTSP(const vector <problem_element> &info){_info = info;};
		~geneticAlgorithmTSP(){};



		/*-----------------------------------------------------------------------

			Funcion que implementa el algoritmo genetico para el TSP

			El tamaño de la poblacion siempre debe ser par para no complicar en exceso

		------------------------------------------------------------------------*/

		SolucionViajante GA(){



		  SolucionViajante bestSolution;
		  int contador = 1;		//Variable con el numero de iteraciones

			_population = initializePopulation(POP_SIZE);	//Inicializamos la poblacion


			evaluatePopulation(_population);
			
			clock_t time = clock();
			double tiempo = 0.0;
			double hora = 3600.0;

			//Tras ordenar, el primer elemento de la poblacion es el mejor
			bestSolution = _population[0];


			while(contador < 100000 && tiempo < (1 * hora))){


				vector <SolucionViajante> auxiliarPopulation;

				//Creamos la nueva poblacion por completo
				while(auxiliarPopulation.size() < _population.size())

					evolvePopulation(auxiliarPopulation);


				evaluatePopulation(auxiliarPopulation);
				_population = auxiliarPopulation;

				if(bestSolution.getFitness() > _population[0].getFitness())
					bestSolution = _population[0];

				cout << "Iteracion: " << contador << "  --> " << bestSolution.getFitness() << endl;


				contador++;
				tiempo = tiempo + ((double) (clock() - time)/CLOCKS_PER_SEC);
			}


		  return bestSolution;
		}




		/*-----------------------------------------------------------------------

			Funcion que genera la poblacion inicial por medio de un método de
			Diversificacion Secuencial:

				Se añaden soluciones a la poblacion que esten separadas
				lo suficiente en el espacio de busqueda (medido por una distancia
				de Hamming)

		------------------------------------------------------------------------*/

		vector <SolucionViajante> initializePopulation(const int &popSize){


		  vector <SolucionViajante> auxiliarPopulation;
		  SolGeneratorViajante solGenerator;

		  SolucionViajante newIndividual;

			for(int i = 0; i < popSize; i++){

				bool valid = false;

				while(! valid){

					valid = true;
					newIndividual = solGenerator.randomSolutionGenerator(_info.size());
					newIndividual.setAptitude(_info);

					//Comprobamos que este lo suficientemente separado del resto de individuos
					for(int j = 0; j < auxiliarPopulation.size(); j++){

						//Comprobamos si la distancia de Hamming es mayor que L/4
						if( distanciaHamming(auxiliarPopulation[j], newIndividual) < (_info.size() / 4) ){

							valid = false;
							break;
						}
					}

				}

				auxiliarPopulation.push_back(newIndividual);

			}

		  return auxiliarPopulation;
		}


		//Funcion que devulve la distancia de hamming entre dos soluciones
		int distanciaHamming(const SolucionViajante &sol1, const SolucionViajante &sol2){

		  int distHamming = 0;

			if(sol1.getSolucion().size() != sol2.getSolucion().size()){

				cout << endl << "Error. El tamaño de los vectores solucion no es similar" << endl << endl;
				exit(0);
			}

			for(int i = 0; i < sol1.getSolucion().size(); i++){

				if(sol1.getSolucion(i) != sol2.getSolucion(i))
					distHamming++;
			}

			return distHamming;
		}




		/*-----------------------------------------------------------------------

			Funcion que ordena los inidividuos de la poblacion en funcion de su
			fitness, en orden descendente (del mejor individuo al peor, es decir,
			de la solucion con menor fitness a la de mayor valor de fitness)

		------------------------------------------------------------------------*/

		void evaluatePopulation(vector <SolucionViajante> &population){


		  unsigned int left = 0, pos = 0, seed = rand();
		  unsigned int stack[MAX];

		  unsigned int len = population.size();


//			cout << endl << "Tamaño poblacion: " << population.size() << endl;

			while (1) {

				for (; left+1 < len; len++){

		            if (pos == MAX)
		            	len = stack[pos = 0];


	            	  double pivot = population[left+seed%(len-left)].getFitness();

		            seed = seed*69069+1;
		            stack[pos++] = len;

					for (unsigned right = left-1; ; ) {

			            while (population[++right].getFitness() < pivot);
			            while (pivot < population[--len].getFitness());

			            if (right >= len)
			            	break;

		              SolucionViajante temp = population[right];

			            population[right] = population[len];
			            population[len] = temp;
					}
				}

	        	if (pos == 0)
			        break;

	        	left = len;
	        	len = stack[--pos];
			}


//			for(int i = 0; i < population.size(); i++)
//				cout << "Fitness " << i << ": " << population[i].getFitness() << endl;

		}






		/*-----------------------------------------------------------------------

			Funcion que escoge a los dos mejores individuos del cruce de dos
			padres de la poblacion dada, y los añade a la nueva poblacion

		------------------------------------------------------------------------*/

		void evolvePopulation(vector <SolucionViajante> &newPopulation){


		  SolucionViajante pA, pB;
		  vector <SolucionViajante> subPopulation;


			selectParents(pA, pB);

			//Obtenemos una subpoblacion con los padres y los hijos que estos generan
			subPopulation = geneticOperator(pA, pB);

			//Dejamos en el vector solo a los dos mejores individuos
			selectIndividuals(subPopulation);

			newPopulation.push_back(subPopulation[0]);
			newPopulation.push_back(subPopulation[1]);
		}





		/*-----------------------------------------------------------------------

			Funcion que selecciona dos padres por el metodo Stochastic Universal
			Sampling, el cual funciona de forma similar al de la Ruleta, pero con
			tantos apuntadores como padres se quieran escoger

		------------------------------------------------------------------------*/

		void selectParents(SolucionViajante &pA, SolucionViajante &pB){


		  vector <SolucionViajante> potentialParents;
		  vector <int> aux;
		  int numAux;


			//Obtenemos padres potenciales de forma aleatoria de la poblacion
			while(potentialParents.size() < 5){

				numAux = rand() % _population.size();
				bool valid = true;

				for(int i = 0; i < aux.size(); i++){

					if(numAux == aux[i])
						valid = false;

				}

				if(valid){

					potentialParents.push_back(_population[numAux]);
					aux.push_back(numAux);
				}

			}

			//Escogemos al mejor individuo de todos para ser uno de los padres
			evaluatePopulation(potentialParents);
			pA = potentialParents[0];


			potentialParents.clear();
			aux.clear();


			//Hacemos el torneo para escoger al SEGUNDO padre
			while(potentialParents.size() < 5){

				numAux = rand() % _population.size();
				bool valid = true;

				for(int i = 0; i < aux.size(); i++){

					if(numAux == aux[i])
						valid = false;

				}

				if(valid){

					potentialParents.push_back(_population[numAux]);
					aux.push_back(numAux);
				}

			}

			evaluatePopulation(potentialParents);
			pB = potentialParents[0];


		}




		/*-----------------------------------------------------------------------

			Funcion que lleva a cabo la reproduccion de dos individuos, escogiendo
			un punto de cruce, para despues ejecutar el algoritmo de entrecruzamiento

		------------------------------------------------------------------------*/


		vector <SolucionViajante> geneticOperator(const SolucionViajante &pA, const SolucionViajante &pB){


		  vector <SolucionViajante> naturalOrder;	//Vector que guarda a toda la familia generada

			naturalOrder.push_back(pA);
			naturalOrder.push_back(pB);


		  int pointA, pointB;

			//Obtenemos dos puntos de cruce diferentes
			pointA = rand() % pA.getSolucion().size();

			do{

				pointB = rand() % pA.getSolucion().size();

			} while(pointB == pointA);

			if(pointA > pointB){

				int aux = pointA;
				pointA = pointB;
				pointB = aux;
			}


			SolucionViajante offspring1 = crossover(pA, pB, pointA, pointB);
			SolucionViajante offspring2 = crossover(pB, pA, pointA, pointB);

			naturalOrder.push_back(offspring1);
			naturalOrder.push_back(offspring2);

		  return naturalOrder;
		}




		//Funcion que lleva a cabo el cruce ordenado (OX) de dos "Cromosomas"
		SolucionViajante crossover(const SolucionViajante &pA, const SolucionViajante &pB, const int &pointA, const int &pointB){



		  SolucionViajante hijo;
		  vector <int> solucion;

		  vector <int> remaining;

			//Rellenamos el vector solucion con las posiciones intermedias del padre A
			for(int i = 0; i < pA.getSolucion().size(); i++){


				if(i < pointA || i > pointB)
					solucion.push_back(-1);

				else
					solucion.push_back(pA.getSolucion(i));


			}

			//Guardamos los elementos sin usar del padre B en orden
			int k = pointA;
			do{

				if( ! buscar(solucion, pB.getSolucion(k)) )
					remaining.push_back(pB.getSolucion(k));


				if(k == solucion.size() - 1)
					k = 0;

				else
					k++;


			} while(k != pointA);



			//Damos los valores sin usar a las zonas que estan fuera de los puntos de cruce
			for(int i = 0; i < solucion.size(); i++){


				if(solucion[i] == -1){

					solucion[i] = remaining[0];
					remaining.erase(remaining.begin());
				}
			}

			hijo.setSolucion(solucion);
			hijo.setAptitude(_info);


		  return hijo;
		}


		bool buscar(const vector <int> &v, const int &n){


			for(int i = 0; i < v.size(); i++){

				if(v[i] == n)
					return true;
			}

		  return false;
		}


		//Funcion que escoge entre los dos mejores individuos despues de un cruce
		void selectIndividuals(vector <SolucionViajante> &naturalOrder){


//			evaluatePopulation(naturalOrder);

			while(naturalOrder.size() > 2)
				naturalOrder.erase( naturalOrder.begin() /* + (naturalOrder.size() - 1)*/ );

		}

};


#endif

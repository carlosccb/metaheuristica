#ifndef		__GENETIC_ALGORITHM_KP__
#define		__GENETIC_ALGORITHM_KP__


#include <cstdlib>
#include <cmath>
#include <vector>

#include "../lib/Miscelanea.hpp"

#include "SolucionMochila.hpp"
#include "SolGeneratorMochila.hpp"
#include "neighborOperatorKP.hpp"
#include "neighborExploratorKP.hpp"
#include "localSearchKP.hpp"

#include <iostream>

#define POP_SIZE2 50
#define MAX 128

using namespace std;



class geneticAlgorithmKP{



	private:

		vector <SolucionMochila> _population;
		vector <problem_element> _info;
		int _KPSize;

	public:


		geneticAlgorithmKP(const vector <problem_element> &info, const int &KPSize){

			_KPSize = KPSize;
			_info = info;
		};

		~geneticAlgorithmKP(){};



		/*-----------------------------------------------------------------------

			Funcion que implementa el algoritmo genetico para el KP

			El tamaño de la poblacion siempre debe ser par para no complicar en exceso

		------------------------------------------------------------------------*/

		SolucionMochila GA(){



		  SolucionMochila bestSolution;
		  int contador = 1;		//Variable con el numero de iteraciones


			_population = initializePopulation(POP_SIZE2);	//Inicializamos la poblacion
			evaluatePopulation(_population);

			//Tras ordenar, el primer elemento de la poblacion es el mejor
			bestSolution = _population[_population.size() - 1];


			while(contador < 2){


			  vector <SolucionMochila> auxiliarPopulation;

				//Creamos la nueva poblacion por completo
				while(auxiliarPopulation.size() < _population.size())

					evolvePopulation(auxiliarPopulation);

				cout << "knapPI_12_500_1000.csv" << endl;

				evaluatePopulation(auxiliarPopulation);
				_population = auxiliarPopulation;

				if(bestSolution.getFitness() > _population[_population.size() - 1].getFitness())
					bestSolution = _population[_population.size() - 1];

				cout << "Iteracion: " << contador << "  --> " << bestSolution.getFitness() << endl;


				contador++;
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

		vector <SolucionMochila> initializePopulation(const int &popSize){


		  vector <SolucionMochila> auxiliarPopulation;
		  SolGeneratorMochila solGenerator;

		  SolucionMochila newIndividual;

			for(int i = 0; i < popSize; i++){

				bool valid = false;

				while(! valid){

					valid = true;
					newIndividual = solGenerator.randomSolutionGenerator(_info.size());
					newIndividual.setAptitude(_KPSize, _info);

					//Comprobamos que este lo suficientemente separado del resto de individuos
					for(int j = 0; j < auxiliarPopulation.size(); j++){

						//Comprobamos si la distancia de Hamming es mayor que L/4
						if( distanciaHamming(auxiliarPopulation[j], newIndividual) < (_info.size() / 4) ){

							valid = false;
							break;
						}
					}

				}

				cout << "Añadido individuo: " << i << endl;
				auxiliarPopulation.push_back(newIndividual);

			}

		  return auxiliarPopulation;
		}


		//Funcion que devulve la distancia de hamming entre dos soluciones
		int distanciaHamming(const SolucionMochila &sol1, const SolucionMochila &sol2){

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

		void evaluatePopulation(vector <SolucionMochila> &population){


		  unsigned int left = 0, pos = 0, seed = rand();
		  unsigned int stack[MAX];

		  unsigned int len = population.size();


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

		              SolucionMochila temp = population[right];

			            population[right] = population[len];
			            population[len] = temp;
					}
				}

	        	if (pos == 0)
			        break;

	        	left = len;
	        	len = stack[--pos];
			}


		}






		/*-----------------------------------------------------------------------

			Funcion que escoge a los dos mejores individuos del cruce de dos
			padres de la poblacion dada, y los añade a la nueva poblacion

		------------------------------------------------------------------------*/

		void evolvePopulation(vector <SolucionMochila> &newPopulation){


		  SolucionMochila pA, pB;
		  vector <SolucionMochila> subPopulation;

			cout << "Antes de la seleccion de padres" << endl;

			selectParents(pA, pB);

			cout << "Antes del Operador de cruce" << endl;

			//Obtenemos una subpoblacion con los padres y los hijos que estos generan
			subPopulation = geneticOperator(pA, pB);

			cout << "Antes de la seleccion de individuos" << endl;

			//Dejamos en el vector solo a los dos mejores individuos
			selectIndividuals(subPopulation);

			cout << "Tras la seleccion de individuos" << endl;

			newPopulation.push_back(subPopulation[0]);
			newPopulation.push_back(subPopulation[1]);
		}





		/*-----------------------------------------------------------------------

			Funcion que selecciona dos padres por el metodo Stochastic Universal
			Sampling, el cual funciona de forma similar al de la Ruleta, pero con
			tantos apuntadores como padres se quieran escoger

		------------------------------------------------------------------------*/

		void selectParents(SolucionMochila &pA, SolucionMochila &pB){



		  vector <double> ruleta;
		  double sumatorioFitness = 0.0;


			for(int i = 0; i < _population.size(); i++){

				ruleta.push_back(sumatorioFitness);				

				sumatorioFitness += _population[i].getFitness();
				//La suma del fitness del ultimo elemento es necesaria

			}

			//Giramos la ruleta y vemos donde se posicionan los apuntadores
		  double numAux = rand() % (int) sumatorioFitness;
		  int posA = -1, posB;

			cout << "numAux = " << numAux << endl;

			for(int i = 0; i < ruleta.size(); i++){

				cout << "ruleta[" << i << "] = " << ruleta[i] << endl;
				if( ruleta[i] > numAux){
					posA = i - 1;
					cout << "Elijo posicion inicial" << endl;
				}
			}

			posB = ( posA + (ruleta.size() / 2) ) % ruleta.size();


			pA = _population[posA];
			pB = _population[posB];
		}




		/*-----------------------------------------------------------------------

			Funcion que lleva a cabo la reproduccion de dos individuos, escogiendo
			un punto de cruce, para despues ejecutar el algoritmo de entrecruzamiento

		------------------------------------------------------------------------*/


		vector <SolucionMochila> geneticOperator(const SolucionMochila &pA, const SolucionMochila &pB){


		  vector <SolucionMochila> naturalOrder;	//Vector que guarda a toda la familia generada

			naturalOrder.push_back(pA);
			naturalOrder.push_back(pB);


		  int pointA, pointB;

//			cout << pB.getSolucion().size() << endl;
			cout << "Antes de la seleccion de los puntos de cruce" << endl;
//			cout << "Tamaño soluciones: A --> " << pA.getSolucion().size() << " B --> " << pB.getSolucion().size();

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

			cout << "Antes del crossover" << endl;

			SolucionMochila offspring1 = crossover(pA, pB, pointA, pointB);
			SolucionMochila offspring2 = crossover(pB, pA, pointA, pointB);

			cout << "Tras el Crossover" << endl;

			naturalOrder.push_back(offspring1);
			naturalOrder.push_back(offspring2);

		  return naturalOrder;
		}




		//Funcion que lleva a cabo el cruce ordenado (OX) de dos "Cromosomas"
		SolucionMochila crossover(const SolucionMochila &pA, const SolucionMochila &pB, const int &pointA, const int &pointB){



		  SolucionMochila hijo;
		  vector <bool> solucion;

		  vector <int> remaining;



			for(int i = 0; i < pA.getSolucion().size(); i++){

				if(i >= pointA && i <= pointB)
					solucion.push_back(pA.getSolucion(i));

				else
					solucion.push_back(pB.getSolucion(i));
			}




			hijo.setSolucion(solucion);
			hijo.setAptitude(_KPSize, _info);


		  return hijo;
		}




		//Funcion que escoge entre los dos mejores individuos despues de un cruce
		void selectIndividuals(vector <SolucionMochila> &naturalOrder){


			while(naturalOrder.size() > 2)
				naturalOrder.erase( naturalOrder.begin() );

		}

};


#endif

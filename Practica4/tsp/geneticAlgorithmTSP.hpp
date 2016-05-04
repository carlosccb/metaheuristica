#ifndef		__GENETIC_ALGORITHM_TSP__
#define		__GENETIC_ALGORITHM_TSP__


#include <cstdlib>
#include <cmath>
#include <vector>

#include "../lib/Miscelanea.hpp"

#include "SolucionViajante.hpp"
#include "SolGeneratorViajante.hpp"
#include "neighborOperatorTSP.hpp"
#include "neighborExploratorTSP.hpp"
#include "localSearchTSP.hpp"

#include <iostream>

#define POP_SIZE 50

using namespace std;



class geneticAlgorithmTSP{



	private:

		vector <SolucionViajante> _population;
		vector <problem_element> _info;

	public:


		geneticAlgorithm(const vector <problem_element> &info){_info = info;};
		~geneticAlgorithm(){};







		/*-----------------------------------------------------------------------

			Funcion que implementa el algoritmo genetico para el TSP

			El tamaño de la poblacion siempre debe ser par para no complicar en exceso

		------------------------------------------------------------------------*/

		SolucionViajante GA(){


			_population = initializePopulation(POP_SIZE);	//Inicializamos la poblacion

			while(/* Condicion de Parada */){

				vector <SolucionViajante> auxiliarPopulation;

				//Creamos la nueva poblacion por completo
				while(auxiliarPopulation.size() < _population.size()){

					generarHijos(auxiliarPopulation);


				}
			}

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

		  SolucionViajante newIndividual = solGenerator.randomSolutionGenerator(_info.size());
		  newIndividual.setAptitude();


			auxiliarPopulation.push_back(newIndividual);
			for(int i = 0; i < popSize; i++){

				bool valid = false;

				while(! valid){

					valid = true;
					newIndividual = solGenerator.randomSolutionGenerator(_info.size());
					newIndividual.setAptitude();

					//Comprobamos que este lo suficientemente separado del resto de individuos
					for(int j = 0; j < auxiliarPopulation.size(); j++){

						//Comprobamos si la distancia de Hamming es mayor que L/4
						if( distanciaHamming(auxiliarPopulation[i], newIndividual) < (_info.size() / 4) )
							valid = false;

					}

				}

				auxiliarPopulation.push_back(newIndividual);

			}

		  return auxiliarPopulation;
		}


		int distaciaHamming(const SolucionViajante &sol1, const SolucionViajante &sol2){








		}

};


#endif

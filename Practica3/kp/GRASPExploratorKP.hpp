#ifndef		__GRASP_EXPLORATOR_KP__
#define		__GRASP_EXPLORATOR_KP__


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



using namespace std;



class GRASPExploratorKP{



	private:

		neighborOperatorKP _operador;
		firstImprovementKP _explorador;
		localSearchKP _busquedaLocal;


	public:


		GRASPExploratorKP(){};
		GRASPExploratorKP(localSearchKP &busquedaLocal, firstImprovementKP &explorador, neighborOperatorKP &operador){

			_busquedaLocal = busquedaLocal;
			_explorador = explorador;
			_operador = operador;
		}


		int mejorCandidato(const vector <problem_element> &info, const vector <int> &candidatos){


			int posMejor = 0;
			double ratioMejor = info[0].a / info[0].b;		//beneficio / peso

			for(int i = 1; i < candidatos.size(); i++){

				double ratioActual = info[i].a / info[i].b;
				if( ratioActual > ratioMejor ){

					posMejor = i;
					ratioMejor = ratioActual;
				}

			}

		  return posMejor;
		}


		SolucionMochila greedyConstructor(const vector <problem_element> &info){


		/*

		Habra n iteraciones (tantas como elementos)

			Para el KP:

				Debemos generar la solucion al completo desde un vector vacio.



				Para ello hay que generar la lista de elementos candidatos a añadir a la solucion (deben ser elementos aun no escogidos)

					La primera ciudad se escoge de forma totalmente aleatoria

					Generarla escogiendo 10 elementos de forma aleatoria
					Ordenarlos despues en base a la distancia con el último nodo añadido al vector
					Escoger la mejor de ellos y volver a hacer la iteracion





			Para el KP:

				Generamos la solucion partiendo de un vector sin ningun elemento escogido (Todo el vector a 0)

				Hay que generar la lista cogiendo elementos de forma aleatoria

					¿Cuantos elementos hay que escoger? 	----> En torno a un 10% o un 5%

					Los elementos escogidos se ordenaran en base a el ratio beneficio/peso

					Se escogera el que lo maximice

		*/



			SolucionMochila solucionFinal;
			vector <int> aux;
			int numAux;


			//Obtenemos el resto de elementos mediante un Greedy con una lista de elemntos aleatorios
			while(info.size() / 10){


				while(aux.size() < 10){	//Creamos una lista con 10 elementos aun no escogidos


					do{

						numAux = rand() % info.size();

					} while(! solucionFinal.getSolucion(numAux));
					aux.push_back(numAux);		//Introducimos en la lista de candidatos un elemento aleatorio que aun no este en la lista
				}

				int mejorPos = mejorCandidato(info, aux);
				solucionFinal.setSolucion(posMejor, true);

				aux.clear();
			}


		  return solucionFinal;
		}
















};

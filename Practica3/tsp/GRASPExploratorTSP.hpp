#ifndef		__GRASP_EXPLORATOR_TSP__
#define		__GRASP_EXPLORATOR_TSP__


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



using namespace std;



class GRASPExploratorTSP{



	private:

		neighborOperatorTSP _operador;
		firstImprovementTSP _explorador;
		localSearchTSP _busquedaLocal;


	public:


		GRASPExploratorTSP(){};
		GRASPExploratorTSP(localSearchTSP &busquedaLocal, firstImprovementTSP &explorador, neighborOperatorTSP &operador){

			_busquedaLocal = busquedaLocal;
			_explorador = explorador;
			_operador = operador;
		}


		//Funcion que da la distancia entre dos ciudades
		double distancia(const problem_element a, const problem_element b) {
			return sqrt(pow(a.a - b.a,2) + pow(a.b - b.b,2));
		}


		
		SolucionViajante greedyConstructor(const vector <problem_element> &info){


		/*

		Habra n iteraciones (tantas como elementos)

			Para el TSP:

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



			int numAux;
			vector <int> aux, aux2, solucionFinal;


			for(int i = 0; i < info.size(); i++)
				aux.push_back(i);	//Vector con las posiciones por añadir aun


			//Obtenemos de forma aleatoria el primer elemento de la solucion
			numAux = rand() % info.size();
			solucionFinal.push_back(numAux);
			aux.erase(aux.begin()+numAux);


			//Obtenemos el resto de elementos mediante un Greedy con una lista de elemntos aleatorios
			while(aux.size() > 0){


				while(aux2.size() < 10){	//Escogemos 10 elementos de los aun no escogidos

					numAux = rand() % info.size();
					for(int i = 0; i < aux2.size(); i++){

						if(aux2.size())
					}
				}

			}



		  return solucionFinal;
		}
















};

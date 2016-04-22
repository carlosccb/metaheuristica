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

		localSearchTSP _busquedaLocal;


	public:


		GRASPExploratorTSP(){};
		GRASPExploratorTSP(localSearchTSP &busquedaLocal){

			_busquedaLocal = busquedaLocal;

		}


		//Funcion que da la distancia entre dos ciudades
		double distancia(const problem_element a, const problem_element b) {
			return sqrt(pow(a.a - b.a,2) + pow(a.b - b.b,2));
		}


		//Funcion que busca si esta presente un valor dentro de un vector de enteros
		bool buscaElemento(const vector <int> &v, const int &num){

			if(v.size() == 0)
				return false;

			for(int i = 0; i < v.size(); i++){

				if(v[i] == num)
					return true;
			}

		  return false;
		}



		int posicionElemento(const vector <int> &v, const int &num){


			for(int i = 0; i < v.size(); i++){

				if(v[i] == num)
					return i;
			}

		  cout << endl << "No se ha encontrado el numero en el vector (GRASPConstructor TSP)" << endl << endl;


		}


		int mejorCandidato(const vector <problem_element> &info, const vector <int> &candidatos, const int &ciudadActual){


			int posMejor = 0;
			double distMejor = distancia( info[ ciudadActual ], info[ candidatos[0] ] );

			for(int i = 1; i < candidatos.size(); i++){


				double distActual = distancia( info[ ciudadActual ], info[ candidatos[i] ] );
				if( distActual < distMejor ){

					posMejor = i;
					distMejor = distActual;
				}
			}

		  return posMejor;
		}

		
		SolucionViajante greedyConstructor(vector <problem_element> &info){


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



			SolucionViajante s;
			vector <int> aux, aux2, solucionFinal;
			int numAux;

			for(int i = 0; i < info.size(); i++)
				aux.push_back(i);	//Vector con las posiciones por añadir aun


			//Obtenemos de forma aleatoria el primer elemento de la solucion
			numAux = rand() % aux.size();
			solucionFinal.push_back(aux[numAux]);
			aux.erase(aux.begin()+numAux);


			//Obtenemos el resto de elementos mediante un Greedy con una lista de elemntos aleatorios
			while(aux.size() > 0){


				while(aux2.size() < 10){	//Creamos una lista con 10 elementos aun no escogidos


					numAux = rand() % aux.size();
					aux2.push_back(aux[numAux]);		//Introducimos en la lista de candidatos un numero aleatorio que aun no este en la lista
				}

				int posMejor = mejorCandidato(info, aux2, solucionFinal[ solucionFinal.size() - 1 ]);
				solucionFinal.push_back( aux2[posMejor] );


				aux.erase( aux.begin() + posicionElemento(aux, aux2[posMejor]) );
				aux2.clear();
			}


			s.setSolucion(solucionFinal);
			s.setAptitude(info);

		  return s;
		}




		SolucionViajante GRASP(vector <problem_element> &info){


			SolucionViajante actualSolution, currentSolution, bestSolution = greedyConstructor(info);
			double actualFitness, bestFitness = bestSolution.getFitness();


			for(int i = 0; i < 100; i++){


				currentSolution = greedyConstructor(info);
				_busquedaLocal.localOptimum(currentSolution, actualSolution, actualFitness);

				if(actualFitness < bestFitness){

					bestSolution = actualSolution;
					bestFitness = actualFitness;
				}
			}

		  return bestSolution;
		}

};


#endif

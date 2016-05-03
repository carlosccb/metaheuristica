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

		localSearchKP _busquedaLocal;


	public:


		GRASPExploratorKP(){};
		GRASPExploratorKP(localSearchKP &busquedaLocal){

			_busquedaLocal = busquedaLocal;
		}


		int mejorCandidato(const vector <problem_element> &info, vector <int> &candidatos){


			int posMejor = candidatos[0];
			double ratioMejor = info[candidatos[0]].a / info[candidatos[0]].b;		//beneficio / peso

			for(int i = 1; i < candidatos.size(); i++){


				double ratioActual = info[candidatos[i]].a / info[candidatos[i]].b;
				if( ratioActual > ratioMejor ){

					posMejor = candidatos[i];
					ratioMejor = ratioActual;
				}

			}

		  return posMejor;
		}



		SolucionMochila greedyConstructor(const vector <problem_element> &info){



			SolucionMochila solucionFinal(info.size());
			vector <int> aux;
			int numAux, i = 0;


			//Obtenemos el resto de elementos mediante un Greedy con una lista de elemntos aleatorios
			while(i < (info.size() / 10)){


				while(aux.size() < 10){	//Creamos una lista con 10 elementos aun no escogidos


					do{

						numAux = rand() % info.size();

					} while(solucionFinal.getSolucion(numAux));
					aux.push_back(numAux);		//Introducimos en la lista de candidatos un elemento aleatorio que aun no este en la lista
				}


				int posMejor = mejorCandidato(info, aux);
				solucionFinal.setSolucion(posMejor, true);

				aux.clear();

				i++;
			}


			solucionFinal.setAptitude(_busquedaLocal.getOperator().getKPSize(), info);

		  return solucionFinal;
		}



		SolucionMochila GRASP(const vector <problem_element> &info){


			SolucionMochila actualSolution, currentSolution, bestSolution = greedyConstructor(info);
			double actualFitness, bestFitness = bestSolution.getFitness();


			for(int i = 0; i < 100; i++){

//				cout << "Iteracion: " << i << endl;
				currentSolution = greedyConstructor(info);
				_busquedaLocal.localOptimum(currentSolution, actualSolution, actualFitness);

				if(actualFitness > bestFitness){

					bestSolution = actualSolution;
					bestFitness = actualFitness;
				}
			}

		  return bestSolution;
		}




};


#endif

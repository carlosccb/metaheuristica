#ifndef		__NEIGHBOR_OPERATOR_TSP__
#define		__NEIGHBOR_OPERATOR_TSP__

#include "../lib/Miscelanea.hpp"
#include "SolucionViajante.hpp"
#include <vector>
#include <cmath>

using namespace std;


class neighborOperatorTSP{


	private:

		vector <problem_element> _info;		//Informacion de las distancias a cada nodo

	public:

		//Constructor vacio
		neighborOperator(){};
		neighborOperator(vector <problem_element> &info){_info = info;};

		//Observadores
		vector <problem_element> getInfo(){return _info;};


		//Sobrecarga operador igual
		neighborOperatorTSP & operator=(const neighborOperatorTSP &s){

			if(this != &s){

				this->_info = s.getInfo();
			}

		  return *this;
		};



		SolucionViajante generateNeighbor(SolucionViajante &initialSolution, int posA, int posB, bool inversion = true){

			int aux;
			SolucionViajante solucion(initialSolution);

			if(posA > posB){

				aux = posA;
				posA = posB;
				posB = aux;
			}
		        
			if( inversion == false){

				aux = solucion.getSolucion(posA);
				solucion.setSolucion(posA, solucion.getSolucion(posB));
				solucion.setSolucion(posB, aux);
				
			} else {

				vector<int> intercambioAux;
				int i;
				for(i = posB; i > posA; i--){
					intercambioAux.push_back(solucion.getSolucion(i));
				}
				
				for(i = posA; i < posB; i++){
					solucion.setSolucion(i, intercambio[i]);
					
				}


				//Re-calculamos el fitness para la solucion

				double difPos = solucion.distancia(_info[posA - 1], _info[posB]) + solucion.distancia(_info[posA], _info[posB + 1]);

				double difNeg = solucion.distancia(_info[posA - 1], _info[posA]) + solucion.distancia(_info[posB], _info[posB + 1]);


				solucion.setFitness( (solucion.getFitness() - difNeg + difPos) );

			}


		  return solucion;				
		}

};

#endif

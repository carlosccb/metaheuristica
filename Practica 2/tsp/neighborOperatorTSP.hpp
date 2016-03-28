#ifndef		__NEIGHBOR_OPERATOR_TSP__
#define		__NEIGHBOR_OPERATOR_TSP__

#include <SolucionViajante>
#include <vector>
#include <cmath>
using namespace std;


class neighborOperator{


	private:



	public:

		//Constructor vacio
		neighborOperator(){};



                SolucionViajante generateNeighbor(SolucionViajante &initialSolution, int posA, int posB, bool inversion = false){
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
                		
                	}
                	
                	
                	
                	
                }



};

#endif

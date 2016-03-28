#ifndef		__NEIGHBOR_OPERATOR__
#define		__NEIGHBOR_OPERATOR__

#include "SolucionMochila.hpp"
#include <vector>
#include <cmath>
using namespace std;



/* De momento lo estoy haciendo todo de forma general para ver como hacerlo


		Quizas podamos implementar en esta clase todo como metodos, pero no 
		se si a lo mejor seria mas coñazo

*/


class neighborOperator{


	private:



	public:

		//Constructor vacio
		neighborOperator(){};


		//Metodo que genera un vecino de una solucion, teniendo en cuenta unos parametros
		SolucionMochila generateNeighbor(SolucionMochila &initialSolution, vector<int> &parametros){

		int i;
		SolucionMochila solucion(initialSolution);
		
		for (i = 0; i < parametros.size(); i++){
			solucion.setSolucion(parametros[i], abs(solucion.getSolucion(parametros[i]) - 1));
		}
				

                return solucion;
		}
		
		SolucionMochila generateNeighbor(SolucionMochila &initialSolution, int pos){

		SolucionMochila solucion(initialSolution);
		solucion.setSolucion(pos, abs(solucion.getSolucion(pos) - 1));
		return solucion;
		}
	

};

#endif

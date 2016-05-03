#ifndef __SOL_GENERATOR_MOCHILA_HPP__
#define __SOL_GENERATOR_MOCHILA_HPP__

#include <vector>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "../lib/Miscelanea.hpp"

using namespace std;


class SolGeneratorMochila{


	public:

		/* ----------------------------------------------------

			Funcion que genera una nueva solucion aleatoria
		decidiendo el numero de elementos que se incluiran en la
		mochila, y despues en que posiciones

		----------------------------------------------------- */

		SolucionMochila randomSolutionGenerator(unsigned int objetos) {
			SolucionMochila solucion(objetos);

/*
			for(unsigned int i = 0; i < objetos; i++)
				solucion.setSolucion(i, false);

			for(unsigned int i = 0; i < objetos; i++)
				if (rand()%2 == 1)
				 solucion.setSolucion(i, true);
*/


			int incluidos = rand() % objetos;
			int pos;

			for (int i = 0; i < incluidos; i++){

				while(true){

					pos = rand() % objetos;
					if(solucion.getSolucion(pos) == false)
						break;

				}

				solucion.setSolucion(pos, true);
			}


			return solucion;
		}


};


#endif

#ifndef __SOL_GENERATOR_VIAJANTE_HPP__
#define __SOL_GENERATOR_VIAJANTE_HPP__


#include "SolucionViajante.hpp"
#include "../lib/Miscelanea.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;


class SolGeneratorViajante{


	public:

		/* ----------------------------------------------------

			Funcion que genera una nueva solucion aleatoria a 
		partir de una permutacion dada, intercambiando N veces
		las posiciones de dos ciudades en el orden del camino 

		----------------------------------------------------- */

		SolucionViajante randomSolutionGenerator(unsigned int objetos){
			
			SolucionViajante solucion(objetos);

			for(unsigned int i = 0; i < objetos; i++)
				solucion.setSolucion(i, i);

			for(unsigned int i = 0; i < objetos; i++)
				 solucion.setSolucion(rand()%objetos, i);

			return solucion;
		}
};


#endif

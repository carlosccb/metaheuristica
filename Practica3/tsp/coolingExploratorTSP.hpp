#ifndef		__COOLING_EXPLORATOR_TSP__
#define		__COOLING_EXPLORATOR_TSP__


#include <cstdlib>
#include <cmath>
#include <vector>

#include "../lib/Miscelanea.hpp"

#include "SolucionViajante.hpp"
#include "SolGeneratorViajante.hpp"
#include "neighborOperatorTSP.hpp"
#include <iostream>


using namespace std;



class coolingExploratorTSP{


	private:

		neighborOperatorTSP _operador;
		double _temperature;		//Hay que darle una temperatura inicial


	public:

		//Constructores
		coolingExploratorTSP(){};
		coolingExploratorTSP(neighborOperatorTSP &operador){

			_operador = operador;

		}


		//Sobrecarga operador igual
		coolingExploratorTSP & operator=(const coolingExploratorTSP &s){

			if(this != &s){

				this->_operador = s.getOperator();
			}

		  return *this;
		};

		//Modificadores
		void setOperator(neighborOperatorTSP &operador){_operador = operador;};

		//Observadores
		neighborOperatorTSP getOperator() const {return _operador;};


		//Funciones pequeñas

		double temperatureRestart(const vector <problem_element> &info){

			/*


				Generar 5 soluciones aleatorias y 1 vecino para cada una de esas soluciones

				Calcular las diferencias de fitness entre cada una con su vecino y calcular la media de las diferencias

				calcularemos la temperatura inicial con la siguiente funcion:

					Tinicial = - media incremento / logaritmo P0

					---> P0 = probabilidad de aceptacion inicial = 0.9 (emepzar con esa)

			*/


		  double media = 0.0;
		  SolGeneratorViajante solGenerator;

			for(unsigned int i = 0; i < 5; i++){


				int pos1 = random() % info.size();
				int pos2 = random() % info.size();

				SolucionViajante original = solGenerator(info.size());
				original.setAptitude(info);
				double fitness1 = original.getFitness();

				SolucionViajante vecino = getOperator().generateNeighbor(original, pos1, pos2);
				double fitness2 = vecino.getFitness();


				media += fabs(fitness2 - fitness1);

			}

			//Dependiendo de si se quiere maximizar o minimizar, sera o no negativa la diferencia
			double Tinicial = (-media) / log(0.9);

		  return Tinicial;
		}

		void coolingDown(){


			//La constante de enfriamiento geometrica debe estar entre 0.5 y 0.99
			_temperature = 0.99 * _temperature;
		}


		bool accept(const double &actualFitness, const double &newFitness){


			//Tener en mente el tipo de optimizacion a la hora de implementar esta funcion

			if(newFitness < actualFitness)
				return true;

			double incE = newFitness - actualFitness;
			double k = 1;	//De donde carajo sale esta constante ????????

			if(exp(-incE/(k * _temperature)) > 0.5)		//0.5 puede ser cambiado (Es el limite para probabilidades binarias)
				return true;


		  return false;
		}






		//Funciones tochas

		SolucionViajante enfriamientoSimuladoTSP(const vector <problem_element> &info, const Solucion Viajante &initialSolution){


			temperatureRestart(info);

		  double actualFitness, newfitness, bestFitness;
		  SolucionViajante bestSolution, actualSolution, newSolution;


			actualSolution = bestSolution = initialSolution;
			actualFitness = bestFitness = bestSolution.getFitness();


			for(unsigned int k = 0; k < 100000; k++){



				int pos1 = random() % initialSolution.getSolution().size();
				int pos2 = random() % initialSolution.getSolution().size();
				newSolution = getOperator().generateNeighbor(actualSolution, pos1, pos2);
				newFitness = newSolution.getFitness();


				//Si la solucion generada es mejor, la guardamos
				if(newFitness < bestFitness){

					bestSolution = newSolution;
					bestFitness = newFitness;
				}


				//Vemos si aceptamos o no la nueva solucion para generar vecinos a partir de ella
				if(accept(actualFitness, newFitness)){

					actualSolution = newSolution;
					actualFitness = newFitness;
				}


				coolingDown();	//Descendemos la temperatura

			}

		
			return bestSolution;

		}


};


#endif

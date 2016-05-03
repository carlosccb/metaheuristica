#ifndef		__COOLING_EXPLORATOR_KP__
#define		__COOLING_EXPLORATOR_KP__


#include <cstdlib>
#include <cmath>
#include <vector>

#include "../lib/Miscelanea.hpp"

#include "SolucionMochila.hpp"
#include "neighborOperatorKP.hpp"
#include <iostream>


using namespace std;



class coolingExploratorKP{


	private:

		neighborOperatorKP _operador;
		double _temperature;		//Hay que darle una temperatura inicial


	public:

		//Constructores
		coolingExploratorKP(){};
		coolingExploratorKP(neighborOperatorKP &operador){

			_operador = operador;

		}


		//Sobrecarga operador igual
		coolingExploratorKP & operator=(const coolingExploratorKP &s){

			if(this != &s){

				this->_operador = s.getOperator();
			}

		  return *this;
		};

		//Modificadores
		void setOperator(neighborOperatorKP &operador){_operador = operador;};

		//Observadores
		neighborOperatorKP getOperator() const {return _operador;};


		//Funciones pequeñas

		void temperatureRestart(const vector <problem_element> &info){



		  double media = 0.0;
		  SolGeneratorMochila solGenerator;

			for(unsigned int i = 0; i < 5; i++){


				int pos1 = random() % info.size();

				SolucionMochila original = solGenerator.randomSolutionGenerator(info.size());
				original.setAptitude(_operador.getKPSize(), info);
				double fitness1 = original.getFitness();

				SolucionMochila vecino = getOperator().generateNeighbor(original, pos1);
				double fitness2 = vecino.getFitness();


				media += fabs(fitness2 - fitness1);

			}

			//Dependiendo de si se quiere maximizar o minimizar, sera o no negativa la diferencia
			_temperature = (-media) / log(0.9);

		}

		void coolingDown(){


			//La constante de enfriamiento geometrica debe estar entre 0.5 y 0.99
			_temperature = 0.7 * _temperature;
		}


		bool accept(const double &actualFitness, const double &newFitness){


			//Tener en mente el tipo de optimizacion a la hora de implementar esta funcion

			if(newFitness > actualFitness)
				return true;

			double incE = actualFitness - newFitness;
			double k = 1;	//De donde carajo sale esta constante ????????

			if(exp(-incE/(k * _temperature)) > 0.5)		//0.5 puede ser cambiado (Es el limite para probabilidades binarias)
				return true;


		  return false;
		}






		//Funciones tochas

		SolucionMochila enfriamientoSimuladoKP(const vector <problem_element> &info, SolucionMochila &initialSolution){


			temperatureRestart(info);

		  double actualFitness, newFitness, bestFitness;
		  SolucionMochila bestSolution, actualSolution, newSolution;


			actualSolution = bestSolution = initialSolution;
			actualFitness = bestFitness = bestSolution.getFitness();


			for(unsigned int k = 0; k < 100000; k++){

//				cout << "Iteracion: " << k << endl;

				int pos1 = random() % initialSolution.getSolucion().size();
				newSolution = getOperator().generateNeighbor(actualSolution, pos1);
				newFitness = newSolution.getFitness();


				//Si la solucion generada es mejor, la guardamos
				if(newFitness > bestFitness){

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

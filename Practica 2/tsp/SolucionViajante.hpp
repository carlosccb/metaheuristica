#ifndef __SOLUCIONVIAJANTE__
#define __SOLUCIONVIAJANTE__


#include <vector>
#include <cmath>

#include "../lib/Miscelanea.hpp"

using namespace std;

class SolucionViajante{

 private:
  vector<int> _solucion;

 public:
    //Observadores
  inline vector<int> getSolucion() const
   {return _solucion;};

  int getSolucion(unsigned int n) const //Para consultar un elemento de la solución
   { if (n <= _solucion.size()-1)
      return _solucion.at(n);
     else 
      return -1;}; 

   //Modificadores
  inline void setSolucion(vector<int> solucion)
   {_solucion = solucion;};
  
  void setSolucion(unsigned int pos, int valor)
   {if (pos <= _solucion.size()-1)
     _solucion[pos]=valor;}; //Para modificar un elemento de la solución


	//Sobrecarga Operador =
	SolucionViajante & operator=(const SolucionViajante &s){

		if(this != &s)

			this->_solucion = s.getSolucion();

	  return *this;

	}

	
	//Sobrecarga del Operador ==
	inline bool & operator==(const SolucionViajante &s){

	
		for(int i = 0; i < this->_solucion.size(); i++){

			if(this->_solucion[i] != s.getSolucion(i))
				return false;

		}

		return true;
	}


	double distancia(const problem_element a, const problem_element b) {
		return sqrt(pow(a.a - b.a,2) + pow(a.b - b.b,2));
	}



	double getAptitude(vector <problem_element> &info){

		double sumatorio = 0.0;

		for(unsigned int i = 0; i < (info.size() - 1); i++){

			//Sumamos la distancia entre el origen y el destino de cada camino de la solucion
			sumatorio += distancia(info[ _solucion[i] ], info[ _solucion[i+1] ]);

		}

		return sumatorio;
	}


     
     
  SolucionViajante(unsigned int objetos=0){
    for (unsigned int i=0; i< objetos; i++)
    _solucion.push_back(i);
  }
 };
#endif

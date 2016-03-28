#ifndef __SOLUCIONMOCHILA__
#define __SOLUCIONMOCHILA__

#include <vector>

#include "../lib/Miscelanea.hpp"

using namespace std;

class SolucionMochila{

 private:
  vector<bool> _solucion;
  double _fitness;
  double _sumaPeso;
  double _sumaProfits;

 public:
    //Observadores
  inline vector<bool> getSolucion() const
   {return _solucion;};

  bool getSolucion(unsigned int n) const //Para consultar un elemento de la solución
   { if (n <= _solucion.size()-1)
      return _solucion[n];
     else 
      return -1;}; 

   //Modificadores
  inline void setSolucion(vector<bool> solucion)
   {_solucion = solucion;};
  
  void setSolucion(unsigned int pos, bool valor)
   {if (pos <= _solucion.size()-1)
     _solucion[pos]=valor;}; //Para modificar un elemento de la solución


	//Sobrecarga Operador =
	SolucionMochila & operator=(const SolucionMochila &s){

		if(this != &s)

			this->_solucion = s.getSolucion();

	  return *this;

	}



	//Sobrecarga del Operador ==
	inline bool & operator==(const SolucionMochila &s){

	
		for(int i = 0; i < this->_solucion.size(); i++){

			if(this->_solucion[i] != s.getSolucion(i))
				return false;

		}

		return true;
	}





	//Sumatorio del peso de la solucion actual
	int pesoSolucion(vector <problem_element> &info){

		if(_solucion.size() != info.size()){

			cout << "Error. El tamaño de los vectores no coincide.";
			exit(0);
		}

	  int sumatorio = 0;

		for(unsigned int i = 0; i < _solucion.size(); i++){


			if (_solucion[i])	//Si el elemento esta incluido, se suma

				sumatorio += info[i].b;
		}

		return sumatorio;
	}


	//Sumatorio del beneficio de la solucion actual
	double beneficioSolucion(vector <problem_element> &info){

		if(_solucion.size() != info.size()){

			cout << "Error. El tamaño de los vectores no coincide.";
			exit(0);
		}

	  double sumatorio = 0;

		for(unsigned int i = 0; i < _solucion.size(); i++){


			if (_solucion[i])	//Si el elemento esta incluido, se suma

				sumatorio += info[i].a;
		}

		return sumatorio;




	}


	//Sumatorio del beneficio de todos los elementos de la instancia
	double beneficioMaximo(vector <problem_element> &info){

		if(_solucion.size() != info.size()){

			cout << "Error. El tamaño de los vectores no coincide.";
			exit(0);
		}

	  double sumatorio = 0;

		for(unsigned int i = 0; i < _solucion.size(); i++){


			sumatorio += info[i].a;
		}

		return sumatorio;
	}



	//Funcion que devuelve la bondad de una solucion
	void setAptitude(const int &KPSize, vector <problem_element> &info){


		double totalSize = pesoSolucion(info);	//Peso de los elementos escogidos

		if(totalSize <= KPSize)

			return beneficioSolucion(info);	//Beneficio de los elementos escogidos


		else{

			double beneSol = beneficioSolucion(info);
			double beneMax = beneficioMaximo(info);

			_fitness = (beneSol - beneMax);
		}

	}

       inline double getFitness(){return _fitness;};
       
       inline void setFitness(double fitness){_fitness = fitness;};

  //Constructor
  SolucionMochila(int objetos=0){
   int i;
   
     for (i=0; i<objetos; i++){
        _solucion.push_back(false);
      }
  }








 };
#endif

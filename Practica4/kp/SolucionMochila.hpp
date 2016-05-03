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


  inline double getSumaPeso() const {return _sumaPeso;};
  inline double getSumaProfits() const {return _sumaProfits;};
  inline double getFitness() const {return _fitness;};



   //Modificadores
  inline void setSolucion(vector<bool> solucion)
   {_solucion = solucion;};

  void setSolucion(unsigned int pos, bool valor)
   {if (pos <= _solucion.size()-1)
     _solucion[pos]=valor;}; //Para modificar un elemento de la solución

  inline void setFitness(double fitness){_fitness = fitness;};
  inline void setSumaPeso(double suma){_sumaPeso = suma;};
  inline void setSumaProfits(double suma){_sumaProfits = suma;};

	//Sobrecarga Operador =
	SolucionMochila & operator=(const SolucionMochila &s){

		if(this != &s){

			this->_solucion = s.getSolucion();
			this->_fitness = s.getFitness();
			this->_sumaPeso = s.getSumaPeso();
			this->_sumaProfits = s.getSumaProfits();
		}

	  return *this;

	}


	//Sumatorio del peso de la solucion actual
	double pesoSolucion(const vector <problem_element> &info){

		if(_solucion.size() != info.size()){

			cout << "Error. El tamaño de los vectores no coincide.";
			exit(0);
		}

	  int sumatorio = 0;

		for(unsigned int i = 0; i < _solucion.size(); i++){


			if (_solucion[i])	//Si el elemento esta incluido, se suma

				sumatorio += info[i].b;
		}

		_sumaPeso = sumatorio;
		return sumatorio;
	}


	//Sumatorio del beneficio de la solucion actual
	double beneficioSolucion(const vector <problem_element> &info){

		if(_solucion.size() != info.size()){

			cout << "Error. El tamaño de los vectores no coincide.";
			exit(0);
		}

	  double sumatorio = 0;

		for(unsigned int i = 0; i < _solucion.size(); i++){


			if (_solucion[i])	//Si el elemento esta incluido, se suma

				sumatorio += info[i].a;
		}
                _sumaProfits = sumatorio;
		return sumatorio;




	}


	//Sumatorio del beneficio de todos los elementos de la instancia
	double beneficioMaximo(const vector <problem_element> &info){

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
	void setAptitude(const int &KPSize, const vector <problem_element> &info){


		double totalSize = pesoSolucion(info);	//Peso de los elementos escogidos

		if(totalSize <= KPSize)

			_fitness = beneficioSolucion(info);		//Beneficio de los elementos escogidos


		else{
                      _fitness = KPSize - totalSize;


		}

	}

        //recalcula el fitness dado un cambio
        void recalcularFitness(int n, vector <problem_element> &info, int const &KPsize){

		  int peso = info[n].b;
		  int beneficio = info[n].a;

			if (getSolucion(n)){ //si lo metemos
				if (getSumaPeso() > KPsize){//si nos pasabamos
					setFitness(getFitness() - peso);
					setSumaPeso(getSumaPeso() + peso);
				} else if (getSumaPeso() + peso > KPsize){ //sino nos pasabamos y ahora si
					setSumaPeso(getSumaPeso() + peso);
					setFitness(getFitness() - getFitness() + KPsize - getSumaPeso());

				 }else{ //si no nos pasamos

					setFitness(getFitness() + beneficio);
					setSumaPeso(getSumaPeso() + peso);
				 }

			} else {//si lo quitamos
				if (getSumaPeso() >= KPsize){//si nos pasabamos
					if ((getSumaPeso() - peso > KPsize)){//si ahora nos seguimos pasando
						setFitness(getFitness() + peso);
						setSumaPeso(getSumaPeso() - peso);
					}else{ //si ahora no nos pasamos
						setSumaPeso(getSumaPeso() - peso);
						setFitness(getFitness() - getFitness() + beneficioSolucion(info));
					}
				}else{ //no nos pasabamos
					setFitness(getFitness() - beneficio);
						setSumaPeso(getSumaPeso() - peso);
				}


			}


        }


  //Constructor
  SolucionMochila(int objetos=0){
   int i;

     for (i=0; i<objetos; i++){
        _solucion.push_back(false);
      }
  }








 };
#endif

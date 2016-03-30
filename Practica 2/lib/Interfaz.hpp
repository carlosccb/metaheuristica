#ifndef __INTERFAZ_HPP__
#define __INTERFAZ_HPP__

#include <iostream>
#include <vector>

#include "Miscelanea.hpp"
#include "Instance.hpp"
#include "../kp/InstanceKP.hpp"
#include "../tsp/InstanceTSP.hpp"

class Interfaz {
	private:
		int opt;
		int optExplo;
		std::string fileName;

		unsigned int _capacity;

	public:
		Interfaz() {}
		~Interfaz() {}

		//Observadores
		std::string getFileName(){ return fileName;};

		unsigned int getCapacity() {return _capacity;}

		int option_menu() {

			do {
				std::cout << "\n\n";
				std::cout << "¿Que problema desea ejecutar?: " << std::endl;
				std::cout << "  1. TSP" << std::endl;
				std::cout << "  2. KP" << std::endl;
				std::cout << "  0. Exit" << std::endl;

				std::cin >> opt;
			} while(0 > opt || opt > 2);

			if(opt == 0)
				return opt;

			do {
				std::cout << "\n\n";
				std::cout << "¿Que tipo de Explorador de Vecindario desea usar?: " << std::endl;
				std::cout << "  1. Primera Mejora" << std::endl;
				std::cout << "  2. Mejor Mejora" << std::endl;
				std::cout << "  0. Exit" << std::endl;

				std::cin >> optExplo;
			} while(0 > opt || opt > 2);

			return optExplo;
		}

		int getOpt() {return opt;}
		int getOptExplo() {return optExplo;}


		std::vector<problem_element> read_instance(int &veces) {
			bool ret = false;
			std::vector<problem_element> inst_v;

			while(not ret) {
				std::string fileName;
				std::cout << "Introduzca el nombre del fichero: ";
				std::cin >> fileName;

				if(opt == 1) {
					fileName =  "tsp/" + fileName;
					InstanceTSP inst(fileName);
					ret = inst.load_instance(inst_v);
				} else if(opt == 2) {
					fileName =  "kp/" + fileName;
					InstanceKP inst(fileName);
					int inst_num;
					std::cout << "¿Que numero de instancia desea cargar?: ";
					std::cin >> inst_num;
					ret = inst.load_instance(inst_v, inst_num);

					_capacity = inst.getCapacity();


				if(not ret)
					std::cerr << "ERROR: El fichero no se pudo abrir.\n";
				}
			}

					std::cout << "Número de veces a ejecutar: ";
					std::cin >> veces;
			return inst_v;
		}

		void print_instance(std::vector<problem_element> &inst_v) {
				std::cout << "\nInstancia :\n";// << instance.inst_num << " de " << instance.fileName << endl;
				for(unsigned int i = 0; i < inst_v.size(); i++)
					std::cout << inst_v[i].id << ": \n  a: " << inst_v[i].a << "\n  b: " << inst_v[i].b << std::endl;
		}
};

#endif

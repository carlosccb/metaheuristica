#ifndef __INTERFAZ_HPP__
#define __INTERFAZ_HPP__

#include <iostream>
#include <vector>

#include "Miscelanea.hpp"
#include "Instance.hpp"
#include "../KP/InstanceKP.hpp"
#include "../TSP/InstanceTSP.hpp"

class Interfaz {
	private:
		int opt;
		std::string fileName;

	public:
		Interfaz() {}
		~Interfaz() {}

		//Observadores
		std::string getFileName(){ return fileName;};

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
				exit(0);

			return opt;
		}

		int getOpt() {return opt;}

		std::vector<problem_element> read_instance() {
			Instance *inst;
			bool ret = false;
			std::vector<problem_element> inst_v;

			while(not ret) {
				std::string fileName;
				std::cout << "Introduzca el nombre del fichero: ";
				std::cin >> fileName;

				if(opt == 1) {
					fileName =  "TSP/" + fileName;
					inst = new InstanceTSP(fileName);
					ret = inst->load_instance(inst_v);
				} else if(opt == 2) {
					fileName =  "KP/" + fileName;
					inst = new InstanceKP(fileName);

					int inst_num;
					std::cout << "¿Que numero de instancia desea cargar?: ";
					std::cin >> inst_num;
					ret = inst->load_instance(inst_v, inst_num);
				}

				if(not ret)
					std::cerr << "ERROR: El fichero no se pudo abrir.\n";
			}

			return inst_v;
		}

		void print_instance(std::vector<problem_element> &inst_v) {
				std::cout << "\nInstancia :";// << instance.inst_num << " de " << instance.fileName << endl;
				for(unsigned int i = 0; i < inst_v.size(); i++)
					std::cout << inst_v[i].id << ": \n  a: " << inst_v[i].a << "\n  b: " << inst_v[i].b << std::endl;
		}
};

#endif

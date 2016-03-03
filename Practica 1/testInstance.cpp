#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "KP/InstanceKP.hpp"
#include "TSP/InstanceTSP.hpp"

using namespace std;

int main(int argc, char** argv) {

	int opt;
	int inst_num;
	vector<problem_element> inst_v;

	do {
		cout << "\n\n";
		cout << "¿De que problema desea cargar su instancia? " << endl;
		cout << "  1. TSP" << endl;
		cout << "  2. KP" << endl;
		cout << "  0. Exit" << endl;

		cin >> opt;

		string fileName;
		if(opt != 0) {
			cout << "Introduzca el nombre del fichero: ";
			cin >> fileName;
		}

		bool ret = false;

		if(opt == 1) {
			fileName =  "TSP/" + fileName;
			InstanceTSP instance(fileName);
			ret = instance.load_instance(inst_v);
		} else if(opt == 2) {
			fileName =  "KP/" + fileName;
			InstanceKP instance(fileName);
			cout << "¿Que numero de instancia desea cargar?: ";
			cin >> inst_num;
			ret = instance.load_instance(inst_v, inst_num);
		}

		if(opt != 0) {
			if(not ret) {
				cerr << "El fichero no se pudo abrir.\n";
				return -1;
			}

			cout << "\nInstancia " << inst_num << " de " << fileName << endl;
			for(unsigned int i = 0; i < inst_v.size(); i++)
				cout << inst_v[i].id << ": \n  a: " << inst_v[i].a << "\n  b: " << inst_v[i].b << endl;
		}

	} while(opt);

	return 0;
}
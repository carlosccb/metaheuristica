#ifndef __INSTANCE_HPP__
#define __INSTANCE_HPP__

#include <fstream>
#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include <vector>

#include "Miscelanea.hpp"

class Instance {
	private:
		std::fstream _file;

		std::string _file_name;
		int _header_lines;
		//Line that contains the length of one specific instance
		int _length_line;
		int _instance_length;
		//value separator
		char _separator;
		//Number of lines between two instances
		int _end_lines;


	public:
		Instance(std::string file_name, int header_lines, int length_line, char separator, int end_lines = 0) 
			: _file_name(file_name), _header_lines(header_lines), _length_line(length_line), _end_lines(end_lines)
		{
			_separator = separator;
		}

		~Instance() 
		{
			if(_file.is_open())
				_file.close();
		}

		//Funcion para leer una instancia determinada de el fichero csv
		bool loadInstance(std::vector<problem_element> &instance, int desired_instance=0) {
			_file.open(_file_name);

			if(not _file.is_open()) {
				std::cerr << "El fichero no se pudo abrir." << std::endl;
				return false;
			}

			bool ret = skip(desired_instance-1);

			if(not ret)
				return ret;

			instance = load();

			_file.close();

			return true;
		}



	//Estas funciones solo son accesibles desde dentro de la clase o de clases que hereden
	protected:
		//Skips n instances
		bool skip(unsigned int n) {
			if(not _file.is_open()) {
				std::cerr << "El fichero esta cerrado." << std::endl;
				return false;
			}

			if(n==0 || n==-1)
				return true;

			try {
				for(unsigned int i = 0; i < n; i++) {
					//Skips the header
					for(unsigned int j = 0; j < _header_lines+1; j++) {
						if(j == _length_line) {
							std::string line;
							_file.ignore(256, ' ');
							_file >> line;
							_instance_length = std::stoi(line);
						}
						else
							_file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
					}

					//Skips the instance
					for(unsigned int j = 0; j < _instance_length; j++)
						_file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

					//Se salta las lineas que separan instancias
					for(unsigned int j = 0; j < _end_lines; j++)
						_file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
				}
			} catch(...) {
				std::cerr << "\n\n# ERROR:\n";
				std::cerr << "#  La instancia que ha querido cargar es mayor al número de instancias que contiene el documento.\n";
				return false;
			}

			return true;
		}

		//Loads the current instance pointed by the file pointer
		std::vector<problem_element> load() {
			std::vector<problem_element> instance;

			if(not _file.is_open()) {
				std::cerr << "El fichero esta cerrado." << std::endl;
				exit(-1);
			}

			//Loads the desired instance
			for(unsigned int i = 0; i < _header_lines; i++) {
				if(i == _length_line) {
					std::string line;
					getline(_file, line);
					const std::string c_line = line;
					std::regex rgx(".* (\\d+) *$");
					std::smatch match;

					if (std::regex_search(c_line.begin(), c_line.end(), match, rgx))
						_instance_length = std::stoi(match[1]);
					else {
						std::cerr << "No se encontro longitud de la instancia en la cabecera del fichero." << std::endl;
						exit(-1);
					}
				}
				else
					_file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
			}

			for(unsigned int i = 0; i < _instance_length; i++) {
				std::string value;
				instance.push_back(problem_element());

				getline(_file, value, _separator);
				instance[i].id = std::stof(value);

				getline(_file, value, _separator);
				instance[i].a = std::stof(value);

				getline(_file, value,'\n');
				instance[i].b = std::stof(value);
			}

			return instance;
		}
};

#endif
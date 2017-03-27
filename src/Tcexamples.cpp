/*
 * Tcexamples.cpp
 *
 *  Created on: 03/02/2017
 *      Author: higo
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
using namespace std;

#include "Tcexamples.h"

	Tcexamples::Tcexamples() {

		_verification = 0;
		// TODO Auto-generated constructor stub

	}

	Tcexamples::~Tcexamples() {
		// TODO Auto-generated destructor stub
	}


	//			Função Carrega o arquivo Log
	//*********************************************************************************************
	string Tcexamples::take_file(string fileS){

		char letter;
		ifstream file;

		file.open(fileS.c_str());
		if(!file.is_open( )){
			cout<<"Could not open file with function!Q\n";
			file.clear( ); //Reset the read object to clear system memory
		}

		// Loads the file into string
		string file_result;
		while (file.get(letter)) {
			file_result = file_result + letter;
		}
		file.close();

		return file_result;
	}

	//			Função trata o Contra Exemplo BOOLECTOR
	//*********************************************************************************************
	void Tcexamples::take_CE_ESBMC_Boolector(string log, int prec){

		// Variáveis de Ajustes
		string command = "";
		string file_log;
		string current_coordinates[2];
		string word = ":x=";
		ostringstream convert;
		string aux_string = "";
	 	size_t position;

		file_log = take_file(log);							// Carrega o Log e
		std::size_t found_F = file_log.find("FAILED");		// Procura pela palavra FAILED no contra exemplo
		std::size_t found_S = file_log.find("SUCCESSFUL");	// Procura pela palavra SUCCESSFUL no contra exemplo

												//
		if(found_F!=std::string::npos){			//	Entra se houver falha no contra exemplo
												//

															//
		 	_verification = 0;								// 	Atribui 0 para variável q identifica o estão do contra exemplo
															//


			position = file_log.rfind(word);										//
																					//
			aux_string = file_log.substr(position + 5,file_log.length());			//
			position = aux_string.find(",");										//	Busca valores de X1 e X2 no contra Exemplo
			current_coordinates[0] = aux_string.substr(0,position);					//
																					//
			aux_string = aux_string.substr(position + 2,aux_string.length());		//
			position = aux_string.find(",");										//
			current_coordinates[1] = aux_string.substr(0,position);					//

																					//
		    double _x1D = convertStringDouble(current_coordinates[0].c_str());		//	Converte Valores de X1 e X2 em string para Double
		    double _x2D = convertStringDouble(current_coordinates[1].c_str());		//


		    if(_x1D > 1000){										//	Para X1
				_x1D = ((_x1D -4294967296)/prec);					//
				_x1 = convertDoubleString(_x1D);					//	Avalia se é um overflow do ESBCM
			}else{													//  arruma o valor
				_x1 = convertDoubleString(_x1D/prec);				//
			}														//

			if(_x2D > 1000){										// Para X2
				_x2D = ((_x2D -4294967296)/prec);					//
				_x2 = convertDoubleString(_x2D);					//	e
			}else{													//	arruma o valor
				_x2 = convertDoubleString(_x2D/prec);				//
			}														//


			//Generates the minimum														//
			command  = "./value_min " + _x1 + " " + _x2 + " > min_temporary.txt";		//	Gera o valor Fobj com x1 e x2 encontrado
			system(command.c_str());													//	Armazena em "min_temporary.txt"


			string minimumS = take_file("min_temporary.txt");					//	Carrega o Fojb gerado
			_fjob = minimumS.substr(0,minimumS.size()).c_str();					//	Converte para float e atribui


		}else if(found_S!=std::string::npos){					//
																// If the verification was successful
			_verification = 1;									// Caso não enconte a falha, "SUCESSO"

		}else {

			cout << "CONTRA EXEMPLO DESCONHECIDO" << endl;

		}

	}

	//	Função trata o Contra Exemplo Z3
	//*********************************************************************************
	void Tcexamples::take_CE_ESBMC_Z3(string log, int prec){

		// Variáveis de Ajustes
		string command = "";
		string file_log;
		string current_coordinates[2];
		string word = ":x=";
		ostringstream convert;
		string aux_string = "";
	 	size_t position;

		file_log = take_file(log);							// Carrega o Log e
		std::size_t found_F = file_log.find("FAILED");		// Procura pela palavra FAILED no contra exemplo
		std::size_t found_S = file_log.find("SUCCESSFUL");	// Procura pela palavra SUCCESSFUL no contra exemplo

												//
		if(found_F!=std::string::npos){			//	Entra se houver falha no contra exemplo
												//

															//
		 	_verification = 0;								// 	Atribui 0 para variável q identifica o estão do contra exemplo
															//


			position = file_log.rfind(word);										//
																					//
			aux_string = file_log.substr(position + 5,file_log.length());			//
			position = aux_string.find(",");										//	Busca valores de X1 e X2 no contra Exemplo
			current_coordinates[0] = aux_string.substr(0,position);					//
																					//
			aux_string = aux_string.substr(position + 2,aux_string.length());		//
			position = aux_string.find(",");										//
			current_coordinates[1] = aux_string.substr(0,position);					//

																					//
		    double _x1D = convertStringDouble(current_coordinates[0].c_str());		//	Converte Valores de X1 e X2 em string para Double
		    double _x2D = convertStringDouble(current_coordinates[1].c_str());		//


		    if(_x1D > 1000){										//	Para X1
				_x1D = ((_x1D -4294967296)/prec);					//
				_x1 = convertDoubleString(_x1D);					//	Avalia se é um overflow do ESBCM
			}else{													//  arruma o valor
				_x1 = convertDoubleString(_x1D/prec);				//
			}														//

			if(_x2D > 1000){										// Para X2
				_x2D = ((_x2D -4294967296)/prec);					//
				_x2 = convertDoubleString(_x2D);					//	e
			}else{													//	arruma o valor
				_x2 = convertDoubleString(_x2D/prec);				//
			}														//


			//Generates the minimum														//
			command  = "./value_min " + _x1 + " " + _x2 + " > min_temporary.txt";		//	Gera o valor Fobj com x1 e x2 encontrado
			system(command.c_str());													//	Armazena em "min_temporary.txt"


			string minimumS = take_file("min_temporary.txt");					//	Carrega o Fojb gerado
			_fjob = minimumS.substr(0,minimumS.size()).c_str();					//	Converte para float e atribui


		}else if(found_S!=std::string::npos){					//
																// If the verification was successful
			_verification = 1;									// Caso não enconte a falha, "SUCESSO"

		}else {

			cout << "CONTRA EXEMPLO DESCONHECIDO" << endl;

		}

	}


//****************************************************************************************************************************
//			Função trata o Contra Exemplo MATHSAT

	void Tcexamples::take_CE_ESBMC_Mathsat(string log, int prec){

		// Variáveis de Ajustes
		string command = "";
		string file_log;
		string current_coordinates[2];
		string word = ":x=";
		ostringstream convert;
		string aux_string = "";
	 	size_t position;

		file_log = take_file(log);							// Carrega o Log e
		std::size_t found_F = file_log.find("FAILED");		// Procura pela palavra FAILED no contra exemplo
		std::size_t found_S = file_log.find("SUCCESSFUL");	// Procura pela palavra SUCCESSFUL no contra exemplo

												//
		if(found_F!=std::string::npos){			//	Entra se houver falha no contra exemplo
												//

															//
		 	_verification = 0;								// 	Atribui 0 para variável q identifica o estão do contra exemplo
															//

			position = file_log.rfind(word);										//
																					//
			aux_string = file_log.substr(position + 5,file_log.length());			//
			position = aux_string.find(",");										//	Busca valores de X1 e X2 no contra Exemplo
			current_coordinates[0] = aux_string.substr(0,position);					//
																					//
			aux_string = aux_string.substr(position + 2,aux_string.length());		//
			position = aux_string.find(",");										//
			current_coordinates[1] = aux_string.substr(0,position);					//

																					//
		    double _x1D = convertStringDouble(current_coordinates[0].c_str());		//	Converte Valores de X1 e X2 em string para Double
		    double _x2D = convertStringDouble(current_coordinates[1].c_str());		//


		    if(_x1D > 1000){										//	Para X1
				_x1D = ((_x1D -4294967296)/prec);					//
				_x1 = convertDoubleString(_x1D);					//	Avalia se é um overflow do ESBCM
			}else{													//  arruma o valor
				_x1 = convertDoubleString(_x1D/prec);				//
			}														//

			if(_x2D > 1000){										// Para X2
				_x2D = ((_x2D -4294967296)/prec);					//
				_x2 = convertDoubleString(_x2D);					//	e
			}else{													//	arruma o valor
				_x2 = convertDoubleString(_x2D/prec);				//
			}														//

			//Generates the minimum														//
			command  = "./value_min " + _x1 + " " + _x2 + " > min_temporary.txt";		//	Gera o valor Fobj com x1 e x2 encontrado
			system(command.c_str());													//	Armazena em "min_temporary.txt"


			string minimumS = take_file("min_temporary.txt");					//	Carrega o Fojb gerado
			_fjob = minimumS.substr(0,minimumS.size()).c_str();					//	Converte para float e atribui


		}else if(found_S!=std::string::npos){					//
																// If the verification was successful
			_verification = 1;									// Caso não enconte a falha, "SUCESSO"

		}else {

			cout << "CONTRA EXEMPLO DESCONHECIDO" << endl;

		}
	}




	//****************************************************************************************************************************
	//			Função trata o Contra Exemplo MATHSAT

	void Tcexamples::take_CE_CBMC_Minisat(string log, int prec){

			// Variáveis de Ajustes
			string command = "";
			string file_log;
			string current_coordinates[2];

			string word1 = "X[0l]=";
			string word2 = "X[1l]=";
			string wordf = "fobj=";
		 	size_t position1;
		 	size_t position2;
		 	size_t positionf;
		 	size_t parenthesis;

			ostringstream convert;
			string aux_string = "";

			file_log = take_file(log);							// Carrega o Log e
			std::size_t found_F = file_log.find("FAILED");		// Procura pela palavra FAILED no contra exemplo
			std::size_t found_S = file_log.find("SUCCESSFUL");	// Procura pela palavra SUCCESSFUL no contra exemplo

													//
			if(found_F!=std::string::npos){			//	Entra se houver falha no contra exemplo
													//

																//
			 	_verification = 0;								// 	Atribui 0 para variável q identifica o estão do contra exemplo
																//

				position1 = file_log.rfind(word1);
				position2 = file_log.rfind(word2);
				positionf = file_log.rfind(wordf);

				aux_string = file_log.substr(position1+6,file_log.length());
				parenthesis = aux_string.find(" ");
				_x1 = aux_string.substr(0,parenthesis);

				aux_string = file_log.substr(position2+6,file_log.length());
				parenthesis = aux_string.find(" ");
				_x2 = aux_string.substr(0,parenthesis);

				aux_string = file_log.substr(positionf+5,file_log.length());
				parenthesis = aux_string.find(" ");
				_fjob = aux_string.substr(0,parenthesis);

				//Generates the minimum														//
//				command  = "./value_min " + _x1 + " " + _x2 + " > min_temporary.txt";		//	Gera o valor Fobj com x1 e x2 encontrado
//				system(command.c_str());													//	Armazena em "min_temporary.txt"

//				string minimumS = take_file("min_temporary.txt");					//	Carrega o Fojb gerado
//				_fjob = minimumS.substr(0,minimumS.size()).c_str();					//	Converte para float e atribui

			}else if(found_S!=std::string::npos){					//
																	// If the verification was successful
				_verification = 1;									// Caso não enconte a falha, "SUCESSO"

			}else {

				cout << "CONTRA EXEMPLO DESCONHECIDO" << endl;

			}
		}







/*
	void Tcexamples::take_CE_ESBMC_C_Boolector(string log, int prec){

		// Variáveis de Ajustes
		string command = "";
		string file_log;
		string current_coordinates[2];
		string word = ":x=";
		ostringstream convert;
		string aux_string = "";
	 	size_t position;

		file_log = take_file(log);								// Carrega o Log e
		std::size_t found_F = file_log.find("FAILED");			// Procura pela palavra FAILED no contra exemplo
		std::size_t found_S = file_log.find("SUCCESSFUL");		// Procura pela palavra SUCCESSFUL no contra exemplo


												//
		if(found_F!=std::string::npos){			//	Entra se houver falha no contra exemplo
												//

															//
		 	_verification = 0;								// 	Atribui 0 para variável q identifica o estão do contra exemplo
															//

			position = file_log.rfind(word);										//
																					//
			aux_string = file_log.substr(position + 5,file_log.length());			//
			position = aux_string.find(",");										//	Busca valores de X1 e X2 no contra Exemplo
			current_coordinates[0] = aux_string.substr(0,position);					//
																					//
			aux_string = aux_string.substr(position + 2,aux_string.length());		//
			position = aux_string.find(",");										//
			current_coordinates[1] = aux_string.substr(0,position);					//


			cout << "---------------------" << endl;				//
			cout << "X1 e X2 no Tratamento" << endl;				//
																	//
			cout << "X2: ";											//	Teste, Imprime para comparar com a conversão em caso de overflow
			cout << current_coordinates[0] << endl;					//
																	//
			cout << "X1: ";											//
			cout << current_coordinates[1] << endl;					//


																	//
		    double _x1D = atof(current_coordinates[0].c_str());		//	Converte Valores de X1 e X2 em string para Double
		    double _x2D = atof(current_coordinates[1].c_str());		//


		    if(_x1D > 1000){										//	Para X1
				_x1D = ((_x1D -4294967296)/prec);					//
				convert << _x1D;									//	Avalia se é um overflow do ESBCM
				_x1 = convert.str();								//	e
			}else{													//  arruma o valor
				_x1 = convertDoubleString(_x1D/prec);						//
			}														//


			if(_x2D > 1000){										// Para X2
				_x2D = ((_x2D -4294967296)/prec);					//
				convert << _x2D;									//	Avalia se é um overflow do ESBCM
				_x2 = convert.str();								//	e
			}else{													//	arruma o valor
				_x2 = convertDoubleString(_x2D/prec);						//
			}														//


			cout << "X1 Conversão: ";								//
			cout << _x1 << endl;									//	Valores de X1 e X2 Arrumados
																	//	Teste, Imprime para comparar com a conversão em caso de overflow
			cout << "X2 Conversão: ";								//
			cout << _x2 << endl;									//


			//Generates the minimum														//
			command  = "./value_min " + _x1 + " " + _x2 + " > min_temporary.txt";		//	Gera o valor Fobj com x1 e x2 encontrado
			system(command.c_str());													//	Armazena em "min_temporary.txt"


			string minimumS = take_file("min_temporary.txt");							//	Carrega o Fojb gerado

//			cout << minimumS << endl;

			_fjob = minimumS;					//	Converte para float e atribui

			cout << "Fobj Final: ";									//
			cout << _fjob << endl;									//	Teste, Imprimri

		}else if(found_S!=std::string::npos){										//
			// If the verification was successful	// Caso não enconte a falha, "SUCESSO"
			_verification = 1;						//

		}else {

			cout << "OUTRO CONTRA EXEMPLO DESCONHECIDO" << endl;

		}
	}
*/


	double Tcexamples::convertStringDouble(string str){
		return atof(str.c_str());
	}

	string Tcexamples::convertDoubleString(double value){
		ostringstream convert;
		convert << value;
		return convert.str();
	}


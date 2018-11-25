//============================================================================
// Name        : optCE.cpp
// Author      : higo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Tflags.h"
#include "Tinput.h"
#include "Setup.h"
#include "Execution.h"
#include "Adjust.h"

using namespace std;
using namespace TFLAGS;
using namespace TINPUT;
using namespace SETUP;
using namespace EXCUTION;

int main(int argc, char *argv[ ]) {

	Tflags flags;
	Tinput input_file;
	Setup  setup_optimization;
	Execution execution_optimization;
	string result_optimization;

	cout << "#########################" << endl;
	cout << "####### OptCE v2.0 ######" << endl;
	cout << "#########################" << endl << endl;



	// Organiza todas as entradas definidas no terminal
	setup_optimization = flags.Checks(argc, argv);

		if(setup_optimization.isInputSetup() == true){

		}else{
			//Imprime mensagem de erro
			return 0;
		}

	// Organiza todos os dados do arquivo de entrada
	setup_optimization = input_file.Checks(setup_optimization);

		if(setup_optimization.isInputFile() == true){

		}else{
			//Imprime mensagem de erro
			return 0;
		}

	// Executa Otimização
	setup_optimization.printSetupExperiment();
	result_optimization = execution_optimization.run(setup_optimization);


	// Apresenta resultados


	return 0;
}


//	Error
//
//	1 - "Incorect extesion";
//
//
//

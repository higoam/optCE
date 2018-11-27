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
	Setup  *setup_optimization_re;
	Execution execution_optimization;
	string result_optimization;

	cout << "#########################" << endl;
	cout << "####### OptCE v2.1 ######" << endl;
	cout << "#########################" << endl << endl;

	// Organiza todas as flags definidas no terminal
	setup_optimization_re = flags.Checks(argc, argv);

		if(setup_optimization_re->hv){
			return 0;
		}

		if(setup_optimization_re->isInputSetup()){

		}else{
			cout << "####### Erro de flag #######" << endl;
			return 0;
		}

	// Organiza todos os dados do arquivo de entrada
	//setup_optimization = input_file.Checks(setup_optimization);

/*		if(setup_optimization_re->isInputFile() == true){

		}else{
			cout << "####### Erro de arquivo entrada #######" << endl;
			return 0;
		}
*/
	// Executa Otimização



		cout << "Algoritmo: ";
		cout << setup_optimization_re->alg << endl;
		cout << "BMC: ";
		cout << setup_optimization_re->bmc << endl;
		cout << "Solver: ";
		cout << setup_optimization_re->solver << endl;

	    result_optimization = execution_optimization.run(setup_optimization_re);


	// Apresenta resultados


	return 0;
}


//	Error
//
//	1 - "Incorect extesion";
//
//
//

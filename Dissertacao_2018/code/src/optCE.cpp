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

		if(setup_optimization_re->hv == true){
			return 0;
		}

		if(!setup_optimization_re->isInputSetup()){
			cout << "####### Erro de flag #######" << endl;
			return 0;
		}

	// Organiza todos os dados do arquivo de entrada
	setup_optimization_re = input_file.Checks(setup_optimization_re);
/*
		if(!setup_optimization_re->isInputFile()){
			cout << "####### Erro de arquivo entrada #######" << endl;
			return 0;
		}
*/
	// Executa Otimização

		cout << endl << "### Parametros Refrente a Flags" << endl << endl;

		cout << "   Nome Função: ";
 		cout << setup_optimization_re->name_function << endl;
 		cout << "   Algoritmo: ";
 		cout << setup_optimization_re->alg << endl;
		cout << "   BMC: ";
		cout << setup_optimization_re->bmc << endl;
		cout << "   Solver: ";
		cout << setup_optimization_re->solver << endl;
		cout << "   Inicialização: ";
		cout << setup_optimization_re->fc << endl;
		cout << "   Biblioteca: ";
		cout << setup_optimization_re->library << endl;
		cout << "   Precisão: ";
		cout << setup_optimization_re->precision << endl;

		cout << endl << "### Parametros Refrente Arquivo de antrada" << endl << endl;

		cout << "   CODE: ";
		cout << setup_optimization_re->code_function << endl;
		cout << "   CODE: ";
		cout << setup_optimization_re->code_function_modified << endl;

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

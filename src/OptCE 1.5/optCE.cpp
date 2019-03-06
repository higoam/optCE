//============================================================================
// Name        : optCE.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <pthread.h>
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
using namespace EXECUTION;


int main(int argc, char *argv[ ]) {

	Tflags flags;
	Tinput input_file;
	Setup  *setup_optimization_re;
	Setup  optimization_Part_1;
	Setup  optimization_Part_2;
	Setup  optimization_Part_3;
	Setup  optimization_Part_4;

    Adjust convertValue;

	Execution execution_optimization;
	string result_optimization;

	// Organiza todas as flags definidas no terminal
	setup_optimization_re = flags.Checks(argc, argv);


	if(setup_optimization_re->hv == true){
		return 0;
	}

	if(setup_optimization_re->getFailure()){
		cout << "####### FIM DE PROGRAMA #######" << endl;
		return 0;
	}

	// Organiza todos os dados do arquivo de entrada
	input_file.Checks(setup_optimization_re);

	if(setup_optimization_re->getFailure()){
		cout << "####### FIM DE PROGRAMA #######" << endl;
		return 0;
	}

	execution_optimization.new_run(setup_optimization_re);


	return 0;
}

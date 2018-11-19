//============================================================================
// Name        : optCE.cpp
// Author      : higo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Tflags.h"
#include "Setup.h"
#include "Execution.h"

using namespace std;
using namespace TFLAGS;
using namespace SETUP;
using namespace EXCUTION;

int main(int argc, char *argv[ ]) {

	Tflags flags;
	Setup  setup_optimization;
	Execution execution_optimization;
	string result_optimization;

	cout << "#########################" << endl;
	cout << "####### OptCE v2.0 ######" << endl;
	cout << "#########################" << endl << endl;

	// Organizes all input data for optimization
	setup_optimization = flags.Checks(argc, argv);

	if(setup_optimization.isAbleInput() == true){

		setup_optimization.printSetupExperiment();

		result_optimization = execution_optimization.run(setup_optimization);

//		cout << "###### Resultado ######" << endl;
//		cout << result_optimization << endl;

	}else{

		// Deve Imprimir a msg de erro
		cout << "com problemas#####" << endl;
		//setup_experiment.
	}

	return 0;
}

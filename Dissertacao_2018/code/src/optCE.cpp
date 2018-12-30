//============================================================================
// Name        : optCE.cpp
// Author      : higo
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
using namespace EXCUTION;

int main(int argc, char *argv[ ]) {

//	pthread_t thread1, thread2;
//	int  iret1, iret2;

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
	setup_optimization_re = input_file.Checks(setup_optimization_re);

	if(setup_optimization_re->getFailure()){
		cout << "####### FIM DE PROGRAMA #######" << endl;
		return 0;
	}


	execution_optimization.run(setup_optimization_re);


//	if(setup_optimization_re->getCore() != 0){

/*
		cout << endl;
		cout << "PARALELO" << endl;
		optimization_Part_1 = *setup_optimization_re;
		optimization_Part_2 = *setup_optimization_re;
		optimization_Part_3 = *setup_optimization_re;
		optimization_Part_4 = *setup_optimization_re;
		cout << endl;

		optimization_Part_1.setSupX1( setup_optimization_re->getSupX1() );
		optimization_Part_1.setInfX1( 0 );
		optimization_Part_1.setSupX2( setup_optimization_re->getSupX2() );
		optimization_Part_1.setInfX2( 0 );
		optimization_Part_1.setCore(1);

		optimization_Part_2.setSupX1( 0 );
		optimization_Part_2.setInfX1( setup_optimization_re->getInfX1() );
		optimization_Part_2.setSupX2( setup_optimization_re->getSupX2() );
		optimization_Part_2.setInfX2( 0 );
		optimization_Part_2.setCore(2);

		optimization_Part_3.setSupX1( 0 );
		optimization_Part_3.setInfX1( setup_optimization_re->getInfX1() );
		optimization_Part_3.setSupX2( 0 );
		optimization_Part_3.setInfX2( setup_optimization_re->getInfX2() );

		optimization_Part_4.setSupX1( setup_optimization_re->getSupX1() );
		optimization_Part_4.setInfX1( 0 );
		optimization_Part_4.setSupX2( 0 );
		optimization_Part_4.setInfX2( setup_optimization_re->getInfX2() );



		//iret1 = pthread_create( &thread1, NULL, Execution::run, (void*) &optimization_Part_1);

		cout << "PARTE 1" << endl;
		cout <<  convertValue.convertDoubleString(optimization_Part_1.l_inf_x1) + " < X1 < " + convertValue.convertDoubleString(optimization_Part_1.l_sup_x1) << endl;
		cout <<  convertValue.convertDoubleString(optimization_Part_1.l_inf_x2) + " < X2 < " + convertValue.convertDoubleString(optimization_Part_1.l_sup_x2) << endl;
		execution_optimization.run(&optimization_Part_1);
		cout << endl;


		if(iret1)
		{
			fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
		    exit(EXIT_FAILURE);
		}


		cout << "PARTE 2" << endl;
		cout <<  convertValue.convertDoubleString(optimization_Part_2.l_inf_x1) + " < X1 < " + convertValue.convertDoubleString(optimization_Part_2.l_sup_x1) << endl;
		cout <<  convertValue.convertDoubleString(optimization_Part_2.l_inf_x2) + " < X2 < " + convertValue.convertDoubleString(optimization_Part_2.l_sup_x2) << endl;
		//result_optimization = execution_optimization.run(&optimization_Part_2);
		cout << endl;

		cout << "PARTE 3" << endl;
		cout <<  convertValue.convertDoubleString(optimization_Part_3.l_inf_x1) + " < X1 < " + convertValue.convertDoubleString(optimization_Part_3.l_sup_x1) << endl;
		cout <<  convertValue.convertDoubleString(optimization_Part_3.l_inf_x2) + " < X2 < " + convertValue.convertDoubleString(optimization_Part_3.l_sup_x2) << endl;
		//result_optimization = execution_optimization.run(&optimization_Part_3);
		cout << endl;


		cout << "PARTE 4" << endl;
		cout <<  convertValue.convertDoubleString(optimization_Part_4.l_inf_x1) + " < X1 < " + convertValue.convertDoubleString(optimization_Part_4.l_sup_x1) << endl;
		cout <<  convertValue.convertDoubleString(optimization_Part_4.l_inf_x2) + " < X2 < " + convertValue.convertDoubleString(optimization_Part_4.l_sup_x2) << endl;
		//result_optimization = execution_optimization.run(&optimization_Part_4);
		cout << endl;


*/

//		cout << "GERAL" << endl;
//		result_optimization = execution_optimization.run(setup_optimization_re);

//	}else{

	//	result_optimization =


//	}


	return 0;
}

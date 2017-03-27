//============================================================================
// Name        : projeto.cpp
// Author      : higo
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <sstream>
using namespace std;

#include "Tflags.h"
#include "Set.h"
#include "Runalgorithm.h"

int main(int argc, char *argv[ ]) {

	Tflags 			flags;
	Set 			experiment;
    Run_algorithm	run;

    // Check input flags and Prepares the inputs to the experiment
	if(flags.Checks(argc, argv)){
		experiment.name_function = flags.get_name_function();
		experiment.mc = flags.get_mc();
		experiment.solver = flags.get_solver();
		experiment.alg = flags.get_alg();
		experiment.l_inf = flags.get_l_inf();
		experiment.l_sup = flags.get_l_sup();
		experiment.fobj_current = flags.get_l_sup();
		experiment.typeData = flags.get_typeData();
		experiment.timeout_global = flags.get_timeout_global();
		experiment.timeout_verification = flags.get_timeout_verification();
		experiment.space_limit = flags.get_name_function();
		experiment.library = flags.get_library();
		experiment.input_format = flags.get_input_formt();
	}else{
		return 0;
	}

	// Check input file
	if(run.checks_input_file(experiment)){

		experiment.nr = run.l_A;
		experiment.n = run.c_A;
		experiment.code_function = run.code_function_original;
		experiment.code_function_modified = run.code_function_treated;

		run.execute_experiment(experiment);

	}else{
		return 0;
	}

	return 0;
}

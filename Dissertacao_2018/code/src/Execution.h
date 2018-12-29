/*
 * Execution.h
 *
 *  Created on: 19/11/2018
 *      Author: higo
 */

#include <math.h>
#include <iostream>
#include "Setup.h"
#include "Adjust.h"
#include "Generatefiles.h"
#include "Tcexamples.h"

using namespace SETUP;
using namespace ADJUST;
using namespace GENERATEFILES;
using namespace TCEXAMPLES;

using namespace std;

#ifndef EXECUTION_H_
#define EXECUTION_H_

namespace EXCUTION {

class Execution {
public:

	Generatefiles generatefilesAUX;
	Tcexamples tratar_contra_exemplo;

    Adjust convertValue;

	Execution();
	virtual ~Execution();

	void * run(Setup* experiment);

    void run_ESBMC_G_BOOLECTOR(Setup* experiment);
    void run_ESBMC_G_Z3(Setup ex);
    void run_ESBMC_G_MATHSAT(Setup ex);

    void run_ESBMC_S_BOOLECTOR(Setup ex);
    void run_ESBMC_S_Z3(Setup ex);
    void run_ESBMC_S_MATHSAT(Setup ex);

    void run_ESBMC_C_BOOLECTOR(Setup ex);
    void run_ESBMC_C_Z3(Setup ex);
    void run_ESBMC_C_MATHSAT(Setup ex);

    void run_CBMC_G_MINISAT(Setup ex);
    void run_CBMC_S_MINISAT(Setup ex);
    void run_CBMC_C_MINISAT(Setup ex);

    bool segment_matrix_format_1(Setup ex, string Mat);
    string remove_space(string str);
    string generate_assumes(Setup* experiment);


};

} /* namespace EXCUTION */

#endif /* EXECUTION_H_ */

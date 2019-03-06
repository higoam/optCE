/*
 * Execution.h
 *
 *  Created on: 30 de jan de 2019
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

namespace EXECUTION {

class Execution {
public:
	Generatefiles generatefilesAUX;
	Tcexamples tratar_contra_exemplo;

    Adjust convertValue;

	Execution();
	virtual ~Execution();

	void new_run(Setup* experiment); //  <-
	void run(Setup* experiment);

    void run_ESBMC_G_BOOLECTOR(Setup* experiment);
    void run_ESBMC_G_Z3(Setup* experiment);
    void run_ESBMC_G_MATHSAT(Setup* experiment);
    void run_ESBMC_G_CVC(Setup* experiment);
    void run_ESBMC_G_YICES(Setup* experiment);

    void run_ESBMC_S_BOOLECTOR(Setup* experiment);
    void run_ESBMC_S_Z3(Setup* experiment);
    void run_ESBMC_S_MATHSAT(Setup* experiment);

    void run_ESBMC_C_BOOLECTOR(Setup* experiment);
    void run_ESBMC_C_Z3(Setup* experiment);
    void run_ESBMC_C_MATHSAT(Setup* experiment);

    void run_CBMC_G_MINISAT(Setup* experiment);
    void run_CBMC_S_MINISAT(Setup* experiment);
    void run_CBMC_C_MINISAT(Setup* experiment);

    void run_CEGIO_G(Setup* experiment); //  <-
    void run_CEGIO_S(Setup* experiment); //  <-
    void run_CEGIO_F(Setup* experiment); //  <-

    void generate_restrictions(Setup* experiment); 				//  <-
    void generate_restrictions_matrix(Setup* experiment); 		//  <-
    void generate_restrictions_equational(Setup* experiment); 	//  <-

    bool segment_matrix_format_1(Setup ex, string Mat);
    string remove_space(string str);
    string generate_assumes(Setup* experiment);
};

} /* namespace EXECUTION */

#endif /* EXECUTION_H_ */

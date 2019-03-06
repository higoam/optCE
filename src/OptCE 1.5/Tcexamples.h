/*
 * Tcexamples.h
 *
 *  Created on: 30 de jan de 2019
 *      Author: higo
 */

#include <math.h>
#include <iostream>
#include "Setup.h"
#include "Adjust.h"
#include "Generatefiles.h"

using namespace SETUP;
using namespace ADJUST;
using namespace GENERATEFILES;

using namespace std;

#ifndef TCEXAMPLES_H_
#define TCEXAMPLES_H_

namespace TCEXAMPLES {

class Tcexamples {
public:
	Tcexamples();
	virtual ~Tcexamples();

    Adjust convertValue;

	string take_file(string fileS);

	void take_CE(string name_file_log, Setup* setup_aux);
	void take_CE_ESBMC_com_For(string name_file_log, Setup* setup_aux);
	void take_CE_ESBMC_sem_For(string name_file_log, Setup* setup_aux);
	void take_CE_CBMC_com_For(string name_file_log, Setup* setup_aux);
	void take_CE_CBMC_sem_For(string name_file_log, Setup* setup_aux);



	void take_CE_ESBMC_Boolector(string name_file_log, Setup* setup_aux);
	void take_CE_ESBMC_Z3(string name_file_log, Setup* setup_aux);
	void take_CE_ESBMC_Mathsat(string name_file_log, Setup* setup_aux);
	void take_CE_ESBMC_CVC(string name_file_log, Setup* setup_aux);
	void take_CE_ESBMC_Yices(string name_file_log, Setup* setup_aux);

	void take_CE_CBMC_MINISAT(string name_file_log, Setup* setup_aux);


};

} /* namespace TCEXAMPLES */

#endif /* TCEXAMPLES_H_ */

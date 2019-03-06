/*
 * Generatefiles.h
 *
 *  Created on: 30 de jan de 2019
 *      Author: higo
 */

#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <sstream>



#include "Setup.h"
#include "Adjust.h"

using namespace SETUP;
using namespace ADJUST;
using namespace std;

#ifndef GENERATEFILES_H_
#define GENERATEFILES_H_

namespace GENERATEFILES {

class Generatefiles {
public:
	Generatefiles();
	virtual ~Generatefiles();

	Adjust convertValue;
	void create_f(Setup* setup_aux);

	void create_specification(Setup* setup_aux);

    // Generation specification files to CEGIO ESBMC
	void create_specification_ESBMC_G_Boolector(Setup* setup_aux);
	void create_specification_ESBMC_G_Z3(Setup* setup_aux);
	void create_specification_ESBMC_G_Mathsat(Setup* setup_aux);

	void create_specification_ESBMC_S_Boolector(Setup* setup_aux);
	void create_specification_ESBMC_S_Z3(Setup* setup_aux);
	void create_specification_ESBMC_S_Mathsat(Setup* setup_aux);

	void create_specification_ESBMC_C_Boolector(Setup* setup_aux);
	void create_specification_ESBMC_C_Z3(Setup* setup_aux);
	void create_specification_ESBMC_C_Mathsat(Setup* setup_aux);

    // Generation specification files to CEGIO CBMC
	void create_specification_CBMC_G_MINISAT(Setup* setup_aux);
	void create_specification_CBMC_S_MINISAT(Setup* setup_aux);
	void create_specification_CBMC_C_MINISAT(Setup* setup_aux);


	void create_specification_CEGIO_G(Setup* setup_aux);
	void create_specification_CEGIO_G_Matrix_com_FOR(Setup* setup_aux);
	void create_specification_CEGIO_G_Matrix_sem_FOR(Setup* setup_aux);
	void create_specification_CEGIO_G_Equational(Setup* setup_aux);

	void create_specification_CEGIO_S(Setup* setup_aux);
	void create_specification_CEGIO_S_Matrix_com_FOR(Setup* setup_aux);
	void create_specification_CEGIO_S_Matrix_sem_FOR(Setup* setup_aux);
	void create_specification_CEGIO_S_Equational(Setup* setup_aux);

	void create_specification_CEGIO_F(Setup* setup_aux);
	void create_specification_CEGIO_F_Matrix_com_FOR(Setup* setup_aux);
	void create_specification_CEGIO_F_Matrix_sem_FOR(Setup* setup_aux);
	void create_specification_CEGIO_F_Equational(Setup* setup_aux);

};

} /* namespace GENERATEFILES */

#endif /* GENERATEFILES_H_ */

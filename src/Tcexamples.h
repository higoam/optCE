/*
 * Tcexamples.h
 *
 *  Created on: 24/11/2018
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

    Adjust convertValue;

	Tcexamples();
	virtual ~Tcexamples();

	string take_file(string fileS);

	void take_CE_ESBMC_Boolector(string name_file_log, Setup* setup_aux);

};

} /* namespace TCEXAMPLES */

#endif /* TCEXAMPLES_H_ */

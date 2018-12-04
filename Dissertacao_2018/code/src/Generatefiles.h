/*
 * Generatefiles.h
 *
 *  Created on: 24/11/2018
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

    //ADJUST convertValue;

	Generatefiles();
	virtual ~Generatefiles();

	void create_f(Setup* setup_aux);
	void create_mi_ESBMC_G_Boolector(Setup* setup_aux);

};

} /* namespace GENERATEFILES */

#endif /* GENERATEFILES_H_ */

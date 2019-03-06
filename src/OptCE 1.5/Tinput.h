/*
 * Tinput.h
 *
 *  Created on: 30 de jan de 2019
 *      Author: higo
 */

#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <list>
#include <math.h>

#include "Setup.h"
#include "Adjust.h"


using namespace SETUP;
using namespace ADJUST;
using namespace std;

#ifndef TINPUT_H_
#define TINPUT_H_

namespace TINPUT {

class Tinput {
public:
	Tinput();
	virtual ~Tinput();

    Adjust convertValue;

    int matrixA[10][10];

	Setup* Checks(Setup* setup_aux);
	Setup* treatment_input_format_standard (Setup* setup_aux);
	Setup* treatment_input_format_constraints(Setup* setup_aux);
	Setup* segment_matrix(Setup* setup_aux);
	string remove_space(string str);


};

} /* namespace TINPUT */

#endif /* TINPUT_H_ */

/*
 * Tinput.h
 *
 *  Created on: 24/11/2018
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

    Adjust convertValue;

    int matrixA[10][10];


	Tinput();
	virtual ~Tinput();

	Setup* Checks(Setup* setup_aux);
	Setup* segment_matrix(Setup* setup_aux);
	string remove_space(string str);

};

} /* namespace TINPUT */

#endif /* TINPUT_H_ */

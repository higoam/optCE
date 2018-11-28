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

using namespace SETUP;
using namespace std;


#ifndef TINPUT_H_
#define TINPUT_H_

namespace TINPUT {

class Tinput {
public:
	Tinput();
	virtual ~Tinput();

	Setup* Checks(Setup* setup_aux);
//	bool Tinput::segment_matrix_format(Setup ex, string Mat);

};

} /* namespace TINPUT */

#endif /* TINPUT_H_ */

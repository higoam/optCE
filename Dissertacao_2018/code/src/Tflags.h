/*
 * Tflags.h
 *
 *  Created on: 19/11/2018
 *      Author: higo
 */

#include <iostream>
#include "Setup.h"

using namespace SETUP;
using namespace std;

#ifndef TFLAGS_H_
#define TFLAGS_H_

namespace TFLAGS {

class Tflags {
public:
	Tflags();
	virtual ~Tflags();

	Setup Checks(int argc, char *argv[]);


};

} /* namespace TFLAGS */

#endif /* TFLAGS_H_ */

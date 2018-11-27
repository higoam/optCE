/*
 * Execution.h
 *
 *  Created on: 19/11/2018
 *      Author: higo
 */

#include <iostream>
#include "Setup.h"

using namespace SETUP;
using namespace std;

#ifndef EXECUTION_H_
#define EXECUTION_H_

namespace EXCUTION {

class Execution {
public:
	Execution();
	virtual ~Execution();

	string run(Setup* experiment);

};

} /* namespace EXCUTION */

#endif /* EXECUTION_H_ */

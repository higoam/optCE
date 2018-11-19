/*
 * Tflags.cpp
 *
 *  Created on: 19/11/2018
 *      Author: higo
 */

#include "Tflags.h"

namespace TFLAGS {

Tflags::Tflags() {
	// TODO Auto-generated constructor stub

}

Tflags::~Tflags() {
	// TODO Auto-generated destructor stub
}

Setup Tflags::Checks(int argc, char *argv[])
{
	Setup setup_experiment;
	setup_experiment.setAbleInput(true);
	setup_experiment.setNameFunction("LEON");
	setup_experiment.setAlg(1);

  return setup_experiment;
}

} /* namespace TFLAGS */

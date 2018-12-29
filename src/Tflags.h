/*
 * Tflags.h
 *
 *  Created on: 19/11/2018
 *      Author: higo
 */
#include <string>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>

#include "Setup.h"
#include "Adjust.h"

using namespace SETUP;
using namespace std;

#ifndef TFLAGS_H_
#define TFLAGS_H_

namespace TFLAGS {

class Tflags {
public:
	Tflags();
	virtual ~Tflags();

	Setup* Checks(int argc, char *argv[]);

	void print_help();
	void print_version();
	string create_value();
	bool check_exist_file(string fileS);
//	Setup check_input_file_format(string name, Setup experiment);
	string check_input_file_format(string name);
	bool check_if_number(string value);
	string get_name_function();
	int get_mc();
	int get_solver();
	int get_alg();
	float get_l_inf();
	string get_l_sup();
	string get_typeData();
	float get_timeout_global();
	float get_timeout_verification();
	string get_library();
	int get_input_formt();
	int get_precision();
};

} /* namespace TFLAGS */

#endif /* TFLAGS_H_ */

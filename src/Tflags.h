/*
 * Tflags.h
 *
 *  Created on: 03/02/2017
 *      Author: higo
 */
#include <iostream>
using namespace std;

#ifndef TFLAGS_H_
#define TFLAGS_H_

class Tflags {

	private:
		string name_function;
		int mc;
		int solver;
		int alg;
		float l_inf;
		string l_sup;
		string typeData;
		float timeout_global;
		float timeout_verification;
		string library;
		int input_formt;

	public:
		Tflags();
		virtual ~Tflags();

		bool Checks(int argc, char *argv[]);

		string take_alg_flags(string alg_l_sup);
		string take_f_i_flags(string alg_l_sup);
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

		void print_version();
		void print_value();
		string create_value();
		bool check_exist_file(string fileS);
		bool check_input_file_format(string name);
		bool check_if_number(string value);

		double convertStringDouble(string str);
		string convertDoubleString(double value);
};

#endif /* TFLAGS_H_ */

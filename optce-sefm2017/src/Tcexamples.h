/*
 *  Tcexamples.h
 *
 *  Created on: 03/02/2017
 *  uthor: Higo Albuquerque
 */

#include <iostream>
using namespace std;

#include "Adjust.h"

#ifndef TCEXAMPLES_H_
#define TCEXAMPLES_H_

	class Tcexamples {

	public:

		int _verification;
		string _x1;
		string _x2;
		string _fjob;

		Ajusts convertValue;

		Tcexamples();
		virtual ~Tcexamples();

		string take_file(string fileS);
		string take_code_function(string name);
		string take_space_limit(string space_limit);

		void take_CE_ESBMC_Boolector(string log, int prec);
		void take_CE_ESBMC_Z3(string log, int prec);
		void take_CE_ESBMC_Mathsat(string log, int prec);


		void take_CE_CBMC_Minisat(string log, int prec);

	};

#endif /* TCEXAMPLES_H_ */

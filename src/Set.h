/*
 * Set.h
 *
 *  Created on: 03/02/2017
 *      Author: higo
 */
#include <iostream>
using namespace std;

#ifndef SET_H_
#define SET_H_

class Set {

	private:

	public:
		string name_function;
		int mc;
		int solver;
		int alg;
		float l_inf;
		string l_sup;
		string fobj_current;
		double _x1;
		double _x2;
		string typeData;
		float timeout_global;
		float timeout_verification;
		string code_function;
		string code_function_modified;
		string space_limit;
		string restrictions;
		int type_restrictions;
		string library;
		int input_format;
		int n;
		int nr;

		Set();
		virtual ~Set();

		void printSet();

		string get_name_function();
		int get_mc();
		int get_solver();
		int get_alg();
		float get_l_inf();
		string get_l_sup();
		string get_typeData();
		float get_timeout();
		string get_sapace_limit();
		string get_code_function();

		void set_name_function(string name_funcP);
		void set_mc(int mcP);
		void set_solver(int solverP);
		void set_alg(int algP);
		void set_l_inf(float l_infP);
		void set_l_sup(string l_supP);
		void set_typeData(int typeDataP);
		void set_timeout(float timeoutP);
		void set_space_limit(string space_limitP);
		void set_code_function(string code_funcP);

};

#endif /* SET_H_ */

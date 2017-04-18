/*
 * Set.cpp
 *
 *  Created on: 03/02/2017
 *      Author: higo
 */

#include "Set.h"

	Set::Set() {

			typeData = "";
			timeout_global = 0;
			timeout_verification = 0;

	}

	Set::~Set() {
		// TODO Auto-generated destructor stub
	}

	void Set::printSet(){
		cout << "####### SET #########"<< endl;
		cout << "Function: " + name_function << endl;
		cout << "F_I: " + l_sup << endl;
		cout <<  mc << endl;
		cout <<  solver << endl;
		cout <<  alg<< endl;
		cout << "TypeData: " + typeData<< endl;
		//cout << "TimeOut: " + timeout<< endl;
		cout << "############################" << endl;
		cout << "CodeFunction:"<< endl;
		cout <<  code_function << endl;
		cout <<  space_limit << endl;

	}


	string Set::get_name_function(){
		return name_function;
	}

	int Set::get_mc(){
		return mc;
	}

	int Set::get_solver(){
		return solver;
	}

	int Set::get_alg(){
		return alg;
	}

	float Set::get_l_inf(){
		return l_inf;
	}

	string Set::get_l_sup(){
		return l_sup;
	}

	string Set::get_typeData(){
		return typeData;
	}

//	float Set::get_timeout_global(){
//		return timeout_global;
//	}

	string Set::get_sapace_limit(){
		return space_limit;
	}

	string Set::get_code_function(){
		return code_function;
	}


	void Set::set_name_function(string name_funcP){
		name_function = name_funcP;
	}

	void Set::set_mc(int mcP){
		mc = mcP;
	}

	void Set::set_solver(int solverP){
		solver = solverP;
	}

	void Set::set_alg(int algP){
		alg = algP;
	}

	void Set::set_l_inf(float l_infP){
		l_inf = l_infP;
	}

	void Set::set_l_sup(string l_supP){
		l_sup = l_supP;
	}

	void Set::set_typeData(int typeDataP){
		typeData = typeDataP;
	}

//	void Set::set_timeout(float timeoutP){
//		timeout = timeoutP;
//	}

	void Set::set_space_limit(string space_limitP){
		space_limit = space_limitP;
	}

	void Set::set_code_function(string code_funcP){
		code_function = code_funcP;
	}

/*
 * 	Ajusts.cpp
 *
 *  Created on: 15/04/2017
 *  Author: Higo Albuquerque
 */



#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>
using namespace std;

#include "Adjust.h"


	Ajusts::Ajusts() 
	{
		// TODO Auto-generated constructor stub

	}

	Ajusts::~Ajusts() 
	{
		// TODO Auto-generated destructor stub
	}

	/*******************************************************************\
	Method: convertStringInt(string str)
	Inputs: Value type string
	Outputs: Value type int
	Purpose: Convert values type string in int
	\*******************************************************************/

	int Ajusts::convertStringInt(string str)
	{
		return atoi(str.c_str());
	}


	/*******************************************************************\
	Method: convertStringDouble(string str)
	Inputs: Value type string
	Outputs: Value type double
	Purpose: Convert values type string in double
	\*******************************************************************/

	double Ajusts::convertStringDouble(string str)
	{
		return atof(str.c_str());
	}


	/*******************************************************************\
	Method: convertStringDouble(string str)
	Inputs: Value type double
	Outputs: Value type string
	Purpose: Convert values type double in string
	\*******************************************************************/

	string Ajusts::convertDoubleString(double value)
	{
		ostringstream convert;
		convert << value;
		return convert.str();
	}


	/*******************************************************************\
	Method: convertIntString(int value)
	Inputs: Value type int
	Outputs: Value type string
	Purpose: Convert values type int in string
	\*******************************************************************/

	string Ajusts::convertIntString(int value)
	{
		ostringstream convert;
		convert << value;
		return convert.str();
	}

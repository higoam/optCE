/*
 * Ajusts.cpp
 *
 *  Created on: 15/04/2017
 *      Author: higo
 */


#include <string>
using namespace std;

#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>

#include "Ajusts.h"


Ajusts::Ajusts() {
	// TODO Auto-generated constructor stub

}

Ajusts::~Ajusts() {
	// TODO Auto-generated destructor stub
}

int Ajusts::convertStringInt(string str){
	return atoi(str.c_str());
}

double Ajusts::convertStringDouble(string str){
	return atof(str.c_str());
}

string Ajusts::convertDoubleString(double value){
	ostringstream convert;
	convert << value;
	return convert.str();
}

string Ajusts::convertIntString(int value){
	ostringstream convert;
	convert << value;
	return convert.str();
}

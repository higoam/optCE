/*
 * Adjust.cpp
 *
 *  Created on: 24/11/2018
 *      Author: higo
 */

#include "Adjust.h"

namespace ADJUST {

Adjust::Adjust() {
	// TODO Auto-generated constructor stub

}

Adjust::~Adjust() {
	// TODO Auto-generated destructor stub
}

int Adjust::convertStringInt(string str)
{
  return atoi(str.c_str());
}

double Adjust::convertStringDouble(string str)
{
  return atof(str.c_str());
}

string Adjust::convertDoubleString(double value)
{
  ostringstream convert;
  convert << value;
  return convert.str();
}

string Adjust::convertIntString(int value)
{
  ostringstream convert;
  convert << value;
  return convert.str();
}

} /* namespace ADJUST */

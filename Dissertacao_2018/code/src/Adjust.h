/*
 * Adjust.h
 *
 *  Created on: 24/11/2018
 *      Author: higo
 */

#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>

using namespace std;

#ifndef ADJUST_H_
#define ADJUST_H_

namespace ADJUST {

class Adjust {
public:
	Adjust();
	virtual ~Adjust();

    int convertStringInt(string str);
    double convertStringDouble(string str);
    string convertDoubleString(double value);
    string convertIntString(int value);
};

} /* namespace ADJUST */

#endif /* ADJUST_H_ */
